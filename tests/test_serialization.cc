#include <catch2/catch_all.hpp>
#include <rll/all.h>

using std::string;
using std::string_view;
using namespace rll;
namespace fs = std::filesystem;

struct DummyConfiguration {
  u32 test = 0;

  struct IpAddress {
    string ip;
    u16 port;

    struct SockMode {
      bool tcp = true;
      bool udp = false;

      NLOHMANN_DEFINE_TYPE_INTRUSIVE(SockMode, tcp, udp)
    } sock_mode {};

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(IpAddress, ip, port, sock_mode)
  } ip_address = {"127.0.0.1", 25'565};

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(DummyConfiguration, test, ip_address)
};

struct TestStruct {
  int a = 1;
  int b = 2;
};
NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(TestStruct, a, b)

struct InterfaceStruct {
  int a = 1;
};

struct DerivedStruct : InterfaceStruct {
  DerivedStruct(int a, int b)
    : InterfaceStruct {a}
    , b {b} {}

  int b = 2;
};

template <>
struct rll::serialization_traits<std::unique_ptr<DerivedStruct>, std::string> {
  [[nodiscard]] static std::string to(std::unique_ptr<DerivedStruct> const& t) {
    return fmt::format("{}x{}", t->a, t->b);
  }

  [[nodiscard]] static std::unique_ptr<DerivedStruct> from(std::string const& j) {
    return std::make_unique<DerivedStruct>(
      std::stoi(j.substr(0, j.find('x'))),
      std::stoi(j.substr(j.find('x') + 1))
    );
  }
};

template <>
struct rll::serialization_traits<TestStruct, std::string> {
  [[nodiscard]] static std::string to(TestStruct const& t) {
    return fmt::format("{}x{}", t.a, t.b);
  }

  [[nodiscard]] static TestStruct from(std::string const& j) {
    return {std::stoi(j.substr(0, j.find('x'))), std::stoi(j.substr(j.find('x') + 1))};
  }
};

TEST_CASE("Serialization & filesystem") {
  SECTION("Custom format") {
    auto const test = TestStruct {1, 2};
    auto const serialized = serializer<std::string>::serialize(test);
    REQUIRE(serialized == "1x2");
    auto const deserialized = serializer<std::string>::deserialize<TestStruct>(serialized);
    REQUIRE(test.a == deserialized.a);
    REQUIRE(test.b == deserialized.b);

    auto const json = serializer<nlohmann::json>::serialize(test);
    REQUIRE(json.dump() == R"({"a":1,"b":2})");
    auto const deserialized_json = serializer<nlohmann::json>::deserialize<TestStruct>(json);
    REQUIRE(test.a == deserialized_json.a);
    REQUIRE(test.b == deserialized_json.b);

    auto const derived = std::make_unique<DerivedStruct>(1, 2);
    auto const serialized_derived = serializer<std::string>::serialize(derived);
    REQUIRE(serialized_derived == "1x2");
    auto const deserialized_derived =
      serializer<std::string>::deserialize<std::unique_ptr<DerivedStruct>>(serialized_derived);
    REQUIRE(derived->a == deserialized_derived->a);
    REQUIRE(derived->b == deserialized_derived->b);
  }

  SECTION("Savefile") {
    SECTION("Basic") {
      {
        auto save = savefile<DummyConfiguration>("test.toml", fs::current_path() / "test-save");

        REQUIRE(save.valid());
        REQUIRE(save().test == 0);
        REQUIRE(save().ip_address.ip == "127.0.0.1");
        REQUIRE(save().ip_address.port == 25'565);
        REQUIRE(save().ip_address.sock_mode.tcp == true);
        REQUIRE(save().ip_address.sock_mode.udp == false);

        auto const serialized = serializer<nlohmann::json>::serialize(save());
        REQUIRE(
          serialized.dump()
          == R"({"ip_address":{"ip":"127.0.0.1","port":25565,"sock_mode":{"tcp":true,"udp":false}},"test":0})"
        );

        save().ip_address = {
          "127.0.0.1",
          45'555,
          {false, true}
        };
        std::ignore = save.save();
        REQUIRE(fs::exists(save.path()));
        REQUIRE(save.has_backup());
        REQUIRE(fs::exists(fs::current_path() / "test-save" / "test.toml.bak"));
        REQUIRE(save().test == 0);
        REQUIRE(save().ip_address.ip == "127.0.0.1");
        REQUIRE(save().ip_address.port == 45'555);
        REQUIRE(save().ip_address.sock_mode.tcp == false);
        REQUIRE(save().ip_address.sock_mode.udp == true);
        save.load();
        REQUIRE(save().test == 0);
        REQUIRE(save().ip_address.ip == "127.0.0.1");
        REQUIRE(save().ip_address.port == 45'555);
        REQUIRE(save().ip_address.sock_mode.tcp == false);
        REQUIRE(save().ip_address.sock_mode.udp == true);
      }

      fs::remove_all(fs::current_path() / "test-save");
    }
  }
}

TEST_CASE("Serialization/deserialization", "[serde]") {
  SECTION("Known types") {
    SECTION("UUID") {
      auto const val = "beb4e77b-406c-4db2-a9bb-97970cf39297"_uuid;
      auto j = nlohmann::json(val);

      REQUIRE(j.get<rll::uuid>() == val);
    }  // UUID

    SECTION("Version") {
      auto const val = "1.2.3"_version;
      auto j = nlohmann::json(val);

      REQUIRE(j.get<rll::version>() == val);
    }  // Version

    SECTION("Optional") {
      SECTION("Some") {
        auto const val = some("beb4e77b-406c-4db2-a9bb-97970cf39297"_uuid);
        auto j = nlohmann::json(val);

        REQUIRE(j.get<optional<rll::uuid>>() == val);
      }  // Some

      SECTION("None") {
        auto const val = optional<rll::uuid>();
        auto j = nlohmann::json(val);

        REQUIRE(j.is_null());
      }  // None
    }  // Optional

    SECTION("Result") {
      SECTION("Ok") {
        auto const val = result<rll::uuid>("beb4e77b-406c-4db2-a9bb-97970cf39297"_uuid);
        auto j = nlohmann::json(val);

        REQUIRE(j.dump() == R"({"ok":true,"value":"beb4e77b-406c-4db2-a9bb-97970cf39297"})");
        REQUIRE(j.get<result<rll::uuid>>() == val);
      }  // Ok

      SECTION("Error") {
        auto const val = result<rll::uuid>(error("Failed to parse UUID"));
        auto j = nlohmann::json(val);

        REQUIRE(j.dump() == R"({"error":"Failed to parse UUID","ok":false})");
        REQUIRE(j.get<result<rll::uuid>>() == val);
      }  // Error
    }  // Result
  }  // Known types
}  // Serialization/deserialization
