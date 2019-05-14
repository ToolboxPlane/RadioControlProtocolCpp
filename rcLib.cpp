//
// Created by paul on 02.10.17.
//
#include "rcLib.hpp"

rcLib::Package::Package() : pkg{} {
    rc_lib_init_rx(&pkg);
}

rcLib::Package::Package(uint16_t resolution, uint8_t channelCount) : pkg{} {
    rc_lib_init_tx(&pkg, resolution, channelCount);
}

uint8_t rcLib::Package::encode() {
    return rc_lib_encode(&pkg);
}

uint8_t rcLib::Package::decode(uint8_t data) {
    return rc_lib_decode(&pkg, data);
}

void rcLib::Package::setChannel(uint8_t channel, uint16_t data) {
    if(data >= pkg.resolution){
        data = static_cast<uint16_t>(this->pkg.resolution - 1);
    }

    if(channel < this->pkg.channel_count) {
        this->pkg.channel_data[channel] = data;
    }
}

void rcLib::Package::setMeshProperties(uint8_t enabled, uint8_t routingLength) {
    this->pkg.mesh = enabled;
    this->pkg.routing_length = routingLength;
}

uint8_t rcLib::Package::getDeviceId() {
    return this->pkg.tid;
}

uint16_t rcLib::Package::getResolution() {
    return this->pkg.resolution;
}

uint16_t rcLib::Package::getChannel(uint8_t channel) {
    if(channel <= this->pkg.channel_count){
        return this->pkg.channel_data[channel];
    } else {
        return static_cast<uint16_t>(-1);
    }
}

uint16_t rcLib::Package::getChannelCount() {
    return this->pkg.channel_count;
}

uint8_t rcLib::Package::isChecksumCorrect() {
    return static_cast<uint8_t>(this->pkg.checksum == rc_lib_calculate_checksum(&this->pkg));
}

uint8_t rcLib::Package::isMesh() {
    return this->pkg.mesh;
}

uint8_t rcLib::Package::needsForwarding() {
    return static_cast<uint8_t>(this->pkg.mesh && this->pkg.routing_length > 0);
}

void rcLib::Package::countNode() {
    this->pkg.routing_length--;
}

uint8_t rcLib::Package::isDiscoverMessage() {
    return rc_lib_is_discover_message(&this->pkg);
}


uint8_t rcLib::Package::isDiscoverResponse() {
    return rc_lib_is_discover_response(&this->pkg);
}

void rcLib::Package::setDiscoverMessage() {
    rc_lib_set_discover_message(&pkg);
}

void rcLib::Package::makeDiscoverResponse(Package responses[], uint8_t len) {
    rc_lib_package_t responses_pkg[len];
    for (uint8_t c = 0; c < len; ++c) {
        responses_pkg[c] = responses[c].pkg;
    }
    rc_lib_make_discover_response(&pkg, responses_pkg, len);
}


uint8_t *rcLib::Package::getEncodedData() {
    return pkg.buffer;
}

void rcLib::Package::setDeviceId(uint8_t deviceId) {
    this->pkg.tid = deviceId;
}

void rcLib::Package::setTransmitterId(uint8_t transmitterId) {
    rc_lib_transmitter_id = transmitterId;
}

uint8_t rcLib::Package::getTransmitterId() {
    return rc_lib_transmitter_id;
}
