/**
 * @file lib.hpp
 * @author Paul Nykiel
 * @version 1.2.1
 */

#ifndef _RC_LIB_PACKAGE_
#define _RC_LIB_PACKAGE_

extern "C" {
#include "RadioControlProtocolC/rc_lib.h"
}

namespace rcLib{

    class Package{
        public:
            /**
             *  Default constructor, should only be used when reading a package
            */
            Package();

            /**
             * Constructor to use when creating a new package
             * @param channelCount  The number of channels used
             * @param resolution The resolution (steps) of each channel.
             */
            Package(uint16_t resolution, uint8_t channelCount);

             /**
             * Read in the next byte for the package
             * @param  data a byte containing package information
             * @return      a boolean, true when the package is finished
             */
            uint8_t decode(uint8_t data);

            /**
             * Convert the package into a serialised byte-array for sending
             * @return a byte array containing the package
             */
            uint8_t encode();

            /**
             * Read the data which should get transmitted
             * @return a pointer to the data, the length is returned by the encode function.
             */
            [[nodiscard]] const uint8_t* getEncodedData() const;

            /**
             * Set the value of one channel. The values get ignored if they are
             * not in the valid range.
             * @param  channel the number of the channel starting from 0
             * @param  data    the value of the channel
             */
            void setChannel(uint8_t channel, uint16_t data);

            /**
             * Get the data of one channel
             * @param  channel the number (starting at 0) of the channel
             * @return         the value of the channel
             */
            [[nodiscard]] uint16_t getChannel(uint8_t channel) const;

            /**
             * Read the amount of channels transmitted by the sender
             * @return the number of channels
             */
            [[nodiscard]] uint16_t getChannelCount() const;

            /**
             * Get the resolution (steps) of each channel
             * @return  The resolution as a uint16_t
             */
            [[nodiscard]] uint16_t getResolution() const;

            /**
             * Get the id of the original sender of the package
             * @return  a uint8_t containing the id
             */
            [[nodiscard]] uint8_t getDeviceId() const;

            /**
             * Set the id of the original sender, this function should only be called if the deviceId != transmitterId.
             * This is the case if you want to simulate packages.
             * @param deviceId
             */
            void setDeviceId(uint8_t deviceId);

            /**
             * Check if the calculated checksum equals the checksum of the package.
             * @return  a boolean whether the checksum is correct
             */
            [[nodiscard]] uint8_t isChecksumCorrect() const;

            /**
             * Read whether the message is a mesh message
             * @return  a boolean wheter the message is a mesh message
             */
            [[nodiscard]] uint8_t isMesh() const;

               /**
             * Set the properties of the package if it is a mesh package
             * @param enabled       a boolean whether the message should be mesh message
             * @param routingLength the maximum amount of nodes one package can traverse
             */
            void setMeshProperties(uint8_t enabled = false,
                                    uint8_t routingLength = 8);

            /**
             * Checks whether the message has already been forwarded
             * @return true if routingLength is larger 0 and the message is a mesh message
             */
            [[nodiscard]] uint8_t needsForwarding() const;

            /**
             * Counts the current node as traversed node by decrementing
             * the routing Length
             */
            void countNode();

            /**
             * @return A boolean wheter the message is a discover message
             */
            [[nodiscard]] uint8_t isDiscoverMessage() const;

            /**
             * @return A boolean wheter the message is a discover response
             */
            [[nodiscard]] uint8_t isDiscoverResponse() const;

            /**
             * Sets the package as a discover message
             */
            void setDiscoverMessage();

            /**
             * Creates an discover response to send back.
             * @param responses all received responses
             * @param len the length of responses
             */
            void makeDiscoverResponse(Package responses[], uint8_t len);

            static void setTransmitterId(uint8_t transmitterId);
            static uint8_t getTransmitterId();
    protected:
            rc_lib_package_t pkg;
    };
}
#endif
