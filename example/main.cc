#include <iostream>

#include "../jsoncxx.hh"

int main() {
	JSON::Value Clothing = JSON::Array({
		JSON::Object({
			{"Type", "Shirt"},
			{"Short", false},
			{"Decoration", "C++ Logo"},
			{"Colors", JSON::Array({
				"Black",
				"White",
				"Blue"
			})}
		}),
		
		JSON::Object({
			{"Type", "Pants"},
			{"Short", true},
			{"Decoration", JSON::Null},
			{"Colors", JSON::Array({
				"Blue"
			})}
		})
	});
	
	std::cout << Clothing.Stringify() << std::endl;

	JSON::Value Table;
	Table["Material"] = "Wood";
	Table["Color"] = "Brown";
	Table["Metrics-cm"] = JSON::Array({100, 50});

	std::cout << Table.Stringify() << std::endl;

	return 0;
};
