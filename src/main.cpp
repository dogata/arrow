#ifndef CSTORE_MAIN_CPP

#include <iostream>
#include <string>
#include <plasma/client.h>
#include <plasma/test_util.h>
#include <arrow/buffer.h>
#include <arrow/status.h>
#include <arrow/util/logging.h>

//using namespace plasma;

int main(int argc, char** argv) {
    /*
    plasma::ObjectID object_id1 = plasma::random_object_id();
    std::cout << "object_id1 is " << object_id1.hex() << std::endl;

    std::string id_string = object_id1.binary();
    plasma::ObjectID object_id2 = plasma::ObjectID::from_binary(id_string);
    std::cout << "object_id2 is " << object_id2.hex() << std::endl;
    */

    // Start up and connect a Plasma client.
    plasma::PlasmaClient client;
    ARROW_CHECK_OK(client.Connect("/tmp/plasma"));

    // Create an object with a fixed ObjectID.
    //ObjectID object_id = ObjectID::from_binary("00000000000000000000");
    plasma::ObjectID object_id = plasma::random_object_id();
    std::cout << "object_id is " << object_id.hex() << std::endl;

    // Check if an object exists.
    bool has_object;
    client.Contains(object_id, &has_object);
    if (has_object) {
        // Object has been created and sealed, proceed
        std::cout << "Object exists!" << std::endl;

        // Disconnect the client.
        ARROW_CHECK_OK(client.Disconnect());

        return 0;
    }

    // Create an object with a fixed ObjectID.
    int64_t data_size = 1000;
    std::shared_ptr<arrow::Buffer> data;
    std::string metadata = "{'author': 'john'}";
    ARROW_CHECK_OK(client.Create(object_id, data_size, (uint8_t*) metadata.data(), metadata.size(), &data));

    // Write some data into the object.
    auto d = data->mutable_data();
    for (int64_t i = 0; i < data_size; i++) {
        d[i] = static_cast<uint8_t>(i % 4);
    }

    // Seal the object.
    ARROW_CHECK_OK(client.Seal(object_id));

    // Retrieve object data.
    plasma::ObjectBuffer object_buffer;
    ARROW_CHECK_OK(client.Get(&object_id, 1, -1, &object_buffer));

    auto buffer = object_buffer.data;
    const uint8_t* data_recv = buffer->data();
    int64_t data_recv_size = buffer->size();

    // Check that the data agrees with what was written in the other process.
    for (int64_t i = 0; i < data_recv_size; i++) {
        ARROW_CHECK(data_recv[i] == static_cast<uint8_t>(i % 4));
    }

    // subsribe to notifications - notifies of data receipt
    /*
    int fd;
    ARROW_CHECK_OK(client.Subscribe(&fd));

    plasma::ObjectID object_id;
    int64_t data_size;
    int64_t metadata_size;
    while (true) {
        ARROW_CHECK_OK(client.GetNotification(fd, &object_id, &data_size, &metadata_size));

        std::cout << "Received object notification for object_id = "
                << object_id.hex() << ", with data_size = " << data_size
                << ", and metadata_size = " << metadata_size << std::endl;
    }
    */

    // Disconnect the client.
    ARROW_CHECK_OK(client.Disconnect());

    return 0;
}

#endif