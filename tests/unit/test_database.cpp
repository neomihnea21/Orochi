#include "../../daemon/include/database.h"
#include "../../lib/doctest.h"

TEST_CASE("Testing Database insert_key") {
    Database* database = new Database();
    database->insert_key("test_1",
                         std::make_shared<Object>(ObjectType::STRING, "10"));
    database->insert_key("test_2",
                         std::make_shared<Object>(ObjectType::STRING, "radu"));

    const std::map<std::string, std::shared_ptr<Object>>& data =
        database->get_data();

    CHECK(data.find("test_1") != data.end());
    CHECK(data.find("test_1")->second.get()->asString() == "10");
    CHECK(data.find("test_2") != data.end());
    CHECK(data.find("test_2")->second.get()->asString() == "radu");
}

TEST_CASE("Testing Database insert_key with different values") {
    Database* database = new Database();
    database->insert_key("test_1",
                         std::make_shared<Object>(ObjectType::STRING, "10"));
    database->insert_key("test_1",
                         std::make_shared<Object>(ObjectType::STRING, "radu"));

    const std::map<std::string, std::shared_ptr<Object>>& data =
        database->get_data();

    CHECK(data.find("test_1") != data.end());
    CHECK(data.find("test_1")->second.get()->asString() == "radu");
}

TEST_CASE("Testing Database select") {
    Database* database = new Database();
    database->insert_key("test_1",
                         std::make_shared<Object>(ObjectType::STRING, "10"));
    database->insert_key("test_2",
                         std::make_shared<Object>(ObjectType::STRING, "radu"));

    CHECK(database->select("test_1").value().get()->asString() == "10");
    CHECK(database->select("test_2").value().get()->asString() == "radu");
    CHECK(database->select("test_3").has_value() == false);
}

TEST_CASE("Testing Database delete_key") {
    Database* database = new Database();
    database->insert_key("test_1",
                         std::make_shared<Object>(ObjectType::STRING, "10"));
    database->insert_key("test_2",
                         std::make_shared<Object>(ObjectType::STRING, "radu"));

    const std::map<std::string, std::shared_ptr<Object>>& data =
        database->get_data();

    CHECK(database->delete_key("test_1").has_value() == true);
    CHECK(database->delete_key("test_2").has_value() == true);
    CHECK(database->delete_key("test_3").has_value() == false);
    CHECK(data.empty());
}
