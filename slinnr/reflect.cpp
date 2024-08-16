#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <tuple>

class Data {
public:
    int i = 1;

    // 定义Data类的getter和setter
    static std::map<std::string, std::tuple<std::function<int(const Data&)>, std::string>> getPropertyGetters() {
        return {
            {"i", {[](const Data& d) { return d.i; }, "int"}}
        };
    }

    static std::map<std::string, std::function<void(Data&, int)>> getPropertySetters() {
        return {
            {"i", [](Data& d, int value) { d.i = value; }}
        };
    }
};

class ReflectData {
public:
    Data data;
    int i = 2;

    // 定义ReflectData的获取器和设置器
    static std::map<std::string, std::tuple<std::function<std::string(const ReflectData&)>, std::string>> getPropertyGetters() {
        return {
            {"i", {[](const ReflectData& rd) { return std::to_string(rd.i); }, "int"}},
            {"data", {[](const ReflectData& rd) { 
                // 通过Data的getter获取data中的属性
                auto dataGetters = Data::getPropertyGetters();
                auto dataGetter = std::get<0>(dataGetters.at("i"));
                std::string dataType = std::get<1>(dataGetters.at("i"));
                return "{ \"i\": " + std::to_string(dataGetter(rd.data)) + " type: " + dataType + " }";
            }, "Data"}}
        };
    }

    static std::map<std::string, std::function<void(ReflectData&, int)>> getPropertySetters() {
        return {
            {"i", [](ReflectData& rd, int value) { rd.i = value; }},
            {"data.i", [](ReflectData& rd, int value) { 
                // 通过Data的setter设置Data中的属性
                Data::getPropertySetters().at("i")(rd.data, value); 
            }}
        };
    }
};

int main() {
    ReflectData rd;

    // 获取ReflectData的getter和setter
    auto getters = ReflectData::getPropertyGetters();
    auto setters = ReflectData::getPropertySetters();

    std::cout << "初始数据和属性:" << std::endl;
    for (const auto& [key, value] : getters) {
        auto [getter, type] = value;
        std::cout << key << " (type: " << type << "): " << getter(rd) << std::endl;
    }

    // 通过setter修改数据
    setters["i"](rd, 42);
    setters["data.i"](rd, 99);

    std::cout << "修改后数据和属性:" << std::endl;
    for (const auto& [key, value] : getters) {
        auto [getter, type] = value;
        std::cout << key << " (type: " << type << "): " << getter(rd) << std::endl;
    }

    return 0;
}