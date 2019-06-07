#include "DataFlash.h"

#include "DataFlash_Backend.h"

const AP_Param::GroupInfo DataFlash_Class::var_info[] = {
    // @Param: _BACKEND_TYPE
    // @DisplayName: DataFlash Backend Storage type
    // @Description: 0 for None, 1 for File, 2 for dataflash mavlink, 3 for both file and dataflash
    // @Values: 0:None,1:File,2:MAVLink,3:BothFileAndMAVLink
    // @User: Standard
    AP_GROUPINFO("_BACKEND_TYPE",  0, DataFlash_Class, _params.backend_types,       DATAFLASH_BACKEND_FILE),

    // @Param: _FILE_BUFSIZE
    // @DisplayName: Maximum DataFlash File Backend buffer size (in kilobytes)
    // @Description: The DataFlash_File backend uses a buffer to store data before writing to the block device.  Raising this value may reduce "gaps" in your SD card logging.  This buffer size may be reduced depending on available memory.  PixHawk requires at least 4 kilobytes.  Maximum value available here is 64 kilobytes.
    // @User: Standard
    AP_GROUPINFO("_FILE_BUFSIZE",  1, DataFlash_Class, _params.file_bufsize,       16),

    AP_GROUPEND
};

void DataFlash_Class::setVehicle_Startup_Log_Writer(vehicle_startup_message_Log_Writer writer)
{
    _vehicle_messages = writer;
}

void DataFlash_Class::set_mission(const AP_Mission *mission) {
    _startup_messagewriter.set_mission(mission);
}

// start functions pass straight through to backend:
bool DataFlash_Class::WriteBlock(const void *pBuffer, uint16_t size) {
    return backend->WriteBlock(pBuffer, size);
}

bool DataFlash_Class::WriteCriticalBlock(const void *pBuffer, uint16_t size) {
    return backend->WriteCriticalBlock(pBuffer, size);
}

bool DataFlash_Class::WritePrioritisedBlock(const void *pBuffer, uint16_t size, bool is_critical) {
    return backend->WritePrioritisedBlock(pBuffer, size, is_critical);
}

uint16_t DataFlash_Class::start_new_log() {
    return backend->start_new_log();
}

// change me to "DoTimeConsumingPreparations"?
void DataFlash_Class::EraseAll() {
    backend->EraseAll();
}
// change me to "LoggingAvailable"?
bool DataFlash_Class::CardInserted(void) {
    return backend->CardInserted();
}

bool DataFlash_Class::NeedPrep() {
    return backend->NeedPrep();
}

void DataFlash_Class::Prep() {
    backend->Prep();
}

uint16_t DataFlash_Class::bufferspace_available(void) {
    return backend->bufferspace_available();
}

uint16_t DataFlash_Class::find_last_log(void) {
    return backend->find_last_log();
}
void DataFlash_Class::get_log_boundaries(uint16_t log_num, uint16_t & start_page, uint16_t & end_page) {
    backend->get_log_boundaries(log_num, start_page, end_page);
}
void DataFlash_Class::get_log_info(uint16_t log_num, uint32_t &size, uint32_t &time_utc) {
    backend->get_log_info(log_num, size, time_utc);
}
int16_t DataFlash_Class::get_log_data(uint16_t log_num, uint16_t page, uint32_t offset, uint16_t len, uint8_t *data) {
    return backend->get_log_data(log_num, page, offset, len, data);
}
uint16_t DataFlash_Class::get_num_logs(void) {
    return backend->get_num_logs();
}
void DataFlash_Class::Log_Fill_Format(const struct LogStructure *s, struct log_Format &pkt) {
    backend->Log_Fill_Format(s, pkt);
}

#ifndef DATAFLASH_NO_CLI
void DataFlash_Class::LogReadProcess(uint16_t log_num,
                                     uint16_t start_page, uint16_t end_page,
                                     print_mode_fn printMode,
                                     AP_HAL::BetterStream *port) {
    backend->LogReadProcess(log_num, start_page, end_page, printMode, port);
}
void DataFlash_Class::DumpPageInfo(AP_HAL::BetterStream *port) {
    backend->DumpPageInfo(port);
}
void DataFlash_Class::ShowDeviceInfo(AP_HAL::BetterStream *port) {
    backend->ShowDeviceInfo(port);
}
void DataFlash_Class::ListAvailableLogs(AP_HAL::BetterStream *port) {
    backend->ListAvailableLogs(port);
}
#endif // DATAFLASH_NO_CLI

bool DataFlash_Class::logging_started(void) {
    return backend->log_write_started;
}

void DataFlash_Class::EnableWrites(bool enable) {
    backend->EnableWrites(enable);
}

void DataFlash_Class::periodic_tasks() {
    backend->periodic_tasks();
}

void DataFlash_Class::WroteStartupFormat() {
    backend->WroteStartupFormat();
}

void DataFlash_Class::WroteStartupParam() {
    backend->WroteStartupParam();
}

#if CONFIG_HAL_BOARD == HAL_BOARD_SITL || CONFIG_HAL_BOARD == HAL_BOARD_LINUX
    // currently only DataFlash_File support this:
void DataFlash_Class::flush(void) {
    backend->flush();
}
#endif

// end functions pass straight through to backend
