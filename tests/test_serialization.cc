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

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(TestStruct, a, b)
};

TEST_CASE("Serialization & filesystem") {
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
