#pragma once

#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <cstdint>

#define JSON_TYPE_NULL    0
#define JSON_TYPE_NUMBER  1
#define JSON_TYPE_INTEGER 2
#define JSON_TYPE_STRING  3
#define JSON_TYPE_BOOL    4
#define JSON_TYPE_ARRAY   5
#define JSON_TYPE_OBJECT  6

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;

typedef uint8_t  ui8;
typedef uint16_t ui16;
typedef uint32_t ui32;

typedef size_t   word;
typedef intmax_t sword;

namespace JSON {
	class Value;

	typedef std::vector <Value> Array;
	typedef std::map <std::string, Value> Object;

	enum null {Null};

	class Value {
		private:
			void Copy(const Value& p_Value) {
				switch (Type) {
					case JSON_TYPE_OBJECT: {
						delete Values.Obj;

						break;
					};

					case JSON_TYPE_ARRAY: {
						delete Values.Arr;

						break;
					};

					case JSON_TYPE_STRING: {
						delete Values.Str;

						break;
					};
				};

				switch (p_Value.Type) {
					case JSON_TYPE_OBJECT: {
						Values.Obj = new Object(p_Value.Values.Obj->begin(), p_Value.Values.Obj->end());

						break;
					};

					case JSON_TYPE_ARRAY: {
						Values.Arr = new Array(p_Value.Values.Arr->begin(), p_Value.Values.Arr->end());

						break;
					};

					case JSON_TYPE_STRING: {
						Values.Str = new std::string(*p_Value.Values.Str);

						break;
					};

					case JSON_TYPE_NUMBER: {
						Values.Num = p_Value.Values.Num;

						break;
					};

					case JSON_TYPE_INTEGER: {
						Values.Int = p_Value.Values.Int;

						break;
					};

					case JSON_TYPE_BOOL: {
						Values.Bool = p_Value.Values.Bool;

						break;
					};
				};

				Type = p_Value.Type;
			};
		public:
			Value():
				Type(JSON_TYPE_NULL),
				Values()
			{};

			Value(std::string p_Str):
				Type(JSON_TYPE_STRING),
				Values(p_Str)
			{};

			Value(const char* p_CStr):
				Type(JSON_TYPE_STRING),
				Values(std::string(p_CStr))
			{};

			Value(double p_Num):
				Type(JSON_TYPE_NUMBER),
				Values(p_Num)
			{};

			Value(sword p_Int):
				Type(JSON_TYPE_INTEGER),
				Values((sword)p_Int)
			{};

			Value(int p_Int):
				Type(JSON_TYPE_INTEGER),
				Values((sword)p_Int)
			{};

			Value(bool p_Bool):
				Type(JSON_TYPE_BOOL),
				Values(p_Bool)
			{};

			Value(const Value& p_Value):
				Type(JSON_TYPE_NULL),
				Values()
			{
				Copy(p_Value);
			};

			Value(null p_Null):
				Type(JSON_TYPE_NULL),
				Values()
			{};

			Value(Array p_Arr):
				Type(JSON_TYPE_ARRAY),
				Values()
			{
				Values.Arr = new Array(p_Arr.begin(), p_Arr.end());
			};

			Value(Object p_Obj):
				Type(JSON_TYPE_OBJECT),
				Values()
			{
				Values.Obj = new Object(p_Obj.begin(), p_Obj.end());
			};

			~Value() {
				switch (Type) {
					case JSON_TYPE_ARRAY: {
						delete Values.Arr;

						break;
					};

					case JSON_TYPE_OBJECT: {
						delete Values.Obj;

						break;
					};

					case JSON_TYPE_STRING: {
						delete Values.Str;

						break;
					};
				};
			};

			Value& operator=(const Value& p_Value) {
				Copy(p_Value);

				return *this;
			};

			Value& operator[](const std::string& p_Idx) {
				switch (Type) {
					case JSON_TYPE_ARRAY: {
						delete Values.Arr;

						break;
					};

					case JSON_TYPE_STRING: {
						delete Values.Str;

						break;
					};
				};

				if (Type != JSON_TYPE_OBJECT) {
					Values.Obj = new Object;
					Type = JSON_TYPE_OBJECT;
				};

				return Values.Obj->operator[](p_Idx);
			};

			Value& operator[](word p_Idx) {
				switch (Type) {
					case JSON_TYPE_OBJECT: {
						delete Values.Obj;

						break;
					};

					case JSON_TYPE_STRING: {
						delete Values.Str;

						break;
					};
				};

				if (Type != JSON_TYPE_ARRAY) {
					Values.Arr = new Array;
					Type = JSON_TYPE_ARRAY;
				};

				return Values.Arr->operator[](p_Idx);
			};

			Value& At(const std::string& p_Idx) const {
				if (Type != JSON_TYPE_OBJECT)
					throw std::runtime_error("Attempt to use At(std::string& p_Idx) on a non-object value");

				return Values.Obj->at(p_Idx);
			};

			Value& At(word p_Idx) const {
				if (Type != JSON_TYPE_ARRAY)
					throw std::runtime_error("Attempt to use At(word& p_Idx) on a non-array value");

				return Values.Arr->at(p_Idx);
			};

			word Length() const {
				if (Type != JSON_TYPE_ARRAY)
					throw std::runtime_error("Attempt to use Length() on a non-array value");

				return Values.Arr->size();
			};

			bool Contains(const std::string& p_Idx) const {
				if (Type != JSON_TYPE_OBJECT)
					throw std::runtime_error("Attempt to use Contains(std::string& p_Idx) on a non-object value");

				return Values.Obj->count(p_Idx);
			};

			bool Contains(word p_Idx) const {
				if (Type != JSON_TYPE_OBJECT)
					throw std::runtime_error("Attempt to use Contains(word& p_Idx) on a non-object value");

				return p_Idx < Values.Arr->size();
			};

			void Push(const Value& p_Value) {
				switch (Type) {
					case JSON_TYPE_OBJECT: {
						delete Values.Obj;

						break;
					};

					case JSON_TYPE_STRING: {
						delete Values.Str;

						break;
					};
				};

				if (Type != JSON_TYPE_ARRAY) {
					Values.Arr = new Array;
					Type = JSON_TYPE_ARRAY;
				};

				Values.Arr->push_back(p_Value);
			};

			word Size() const {
				switch (Type) {
					case JSON_TYPE_ARRAY: {
						return Values.Arr->size();

						break;
					};

					case JSON_TYPE_OBJECT: {
						return Values.Obj->size();

						break;
					};

					default: {
						throw std::runtime_error("Attempt to use Size() on a non-array and non-object value");

						break;
					};
				};
			};

			void Clear() {
				switch (Type) {
					case JSON_TYPE_ARRAY: {
						Values.Arr->clear();

						break;
					};

					case JSON_TYPE_OBJECT: {
						Values.Obj->clear();

						break;
					};

					default: {
						throw std::runtime_error("Attempt to use Clear() on a non-array and non-object value");

						break;
					};
				};
			};

			bool GetType() const {
				return Type;
			};

			double& AsNumber() {
				if (Type != JSON_TYPE_NUMBER)
					throw std::runtime_error("Attempt to use AsNumber() on a non-number value");

				return Values.Num;
			};

			sword& AsInteger() {
				if (Type != JSON_TYPE_INTEGER)
					throw std::runtime_error("Attempt to use AsInteger() on a non-integer value");

				return Values.Int;
			};

			std::string& AsString() {
				if (Type != JSON_TYPE_STRING)
					throw std::runtime_error("Attempt to use AsString() on a non-string value");

				return *Values.Str;
			};

			bool& AsBoolean() {
				if (Type != JSON_TYPE_BOOL)
					throw std::runtime_error("Attempt to use AsBoolean() on a non-boolean value");

				return Values.Bool;
			};

			Array& AsArray() {
				if (Type != JSON_TYPE_ARRAY)
					throw std::runtime_error("Attempt to use AsArray() on a non-array value");

				return *Values.Arr;
			};
			Object& AsObject() {
				if (Type != JSON_TYPE_OBJECT)
					throw std::runtime_error("Attempt to use AsObject() on a non-object value");

				return *Values.Obj;
			};

			std::string Stringify() const {
				std::string Stringified = "";

				switch (Type) {
					case JSON_TYPE_NUMBER: {
						Stringified = std::to_string(Values.Num);

						break;
					};

					case JSON_TYPE_INTEGER: {
						Stringified = std::to_string(Values.Int);

						break;
					};

					case JSON_TYPE_BOOL: {
						Stringified = Values.Bool? "true" : "false";

						break;
					};

					case JSON_TYPE_STRING: {
						Stringified = "\"" + JSONEscape(*Values.Str) + "\"";

						break;
					};

					case JSON_TYPE_ARRAY: {
						Stringified += "[";
						bool Start = true;

						for (const Value &Val : *Values.Arr) {
							if (Start)
								Start = false;
							else
								Stringified += ",";

							Stringified += Val.Stringify();
						};

						Stringified += "]";

						break;
					};

					case JSON_TYPE_OBJECT: {
						Stringified += "{";
						bool Start = true;

						for (const std::pair<const std::string&, const Value&> &Val : *Values.Obj) {
							if (Start)
								Start = false;
							else
								Stringified += ",";

							Stringified += "\"" + Val.first + "\":" + Val.second.Stringify();
						};

						Stringified += "}";

						break;
					};

					case JSON_TYPE_NULL: default: {
						Stringified = "null";
					};
				};

				return Stringified;
			};

		private:
			std::string JSONEscape(const std::string &p_Str) const {
				std::string Escaped = "";

				for (word i = 0; i < p_Str.length(); ++ i)
					switch (p_Str[i]) {
						case '\n': Escaped += "\\";   break;
						case '\r': Escaped += "\\r";  break;
						case '\t': Escaped += "\\t";  break;
						case '\f': Escaped += "\\f";  break;
						case '\b': Escaped += "\\b";  break;
						case '\\': Escaped += "\\\\"; break;
						case '\"': Escaped += "\\\""; break;
						
						default: Escaped += p_Str[i]; break;
					};

				return Escaped;
			};

			ui8 Type;

			union Data {
				Data():
					Bool(0)
				{};

				~Data() {};

				Data(double p_Num):
					Num(p_Num)
				{};

				Data(sword p_Int):
					Int(p_Int)
				{};

				Data(std::string p_Str):
					Str(new std::string(p_Str))
				{};

				Data(bool p_Bool):
					Bool(p_Bool)
				{};

				double Num;
				sword Int;
				std::string* Str;
				bool Bool;
				Array* Arr;
				Object* Obj;
			} Values;
	};
};
