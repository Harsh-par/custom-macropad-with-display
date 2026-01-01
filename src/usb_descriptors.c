#include "tusb.h"

tusb_desc_device_t const desc_device = {
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = 0x0200,
    .bDeviceClass       = 0x00,       
    .bDeviceSubClass    = 0x00,
    .bDeviceProtocol    = 0x00,
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
    .idVendor           = 0x00AB,
    .idProduct          = 0x00CD,
    .bcdDevice          = 0x0100,
    .iManufacturer      = 0x01,
    .iProduct           = 0x02,
    .iSerialNumber      = 0x03,
    .bNumConfigurations = 0x01
};
\
uint8_t const desc_configuration[] = {
    0x09, 0x02,
    0x22, 0x00,  
    0x01,         
    0x01,        
    0x00,         
    0x80,        
    0x32,      

    0x09, 0x04,
    0x00, 0x00, 0x01,
    0x03, 0x01, 0x01, 0x00, 

    0x09, 0x21,
    0x11, 0x01,      
    0x00,             
    0x01,           
    0x22, 63, 0x00,  

    0x07, 0x05,
    0x81, 0x03,    
    0x08, 0x00,       
    0x0A            
};

uint8_t const hid_report_desc[] = {
    0x05, 0x01,        
    0x09, 0x06,        
    0xA1, 0x01,        
    0x05, 0x07,       
    0x19, 0xE0,       
    0x29, 0xE7,        
    0x15, 0x00,       
    0x25, 0x01,       
    0x75, 0x01,       
    0x95, 0x08,    
    0x81, 0x02,    
    0x95, 0x01,      
    0x75, 0x08,        
    0x81, 0x01,        
    0x95, 0x05,        
    0x75, 0x01,      
    0x05, 0x08,       
    0x19, 0x01,      
    0x29, 0x05,       
    0x91, 0x02,        
    0x95, 0x01,
    0x75, 0x03,
    0x91, 0x01,        
    0x95, 0x06,
    0x75, 0x08,
    0x15, 0x00,
    0x25, 0x65,
    0x05, 0x07,
    0x19, 0x00,
    0x29, 0x65,
    0x81, 0x00,        
    0xC0               
};

//These cb need to exist even if not used

uint8_t const* tud_descriptor_device_cb(void) {
    return (uint8_t const*)&desc_device;
}

uint8_t const* tud_descriptor_configuration_cb(uint8_t index) {
    (void) index;
    return desc_configuration;
}

uint8_t const* tud_hid_descriptor_report_cb(uint8_t instance) {
    (void) instance;
    return hid_report_desc;
}

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen){
    (void) instance; (void) report_id; (void) report_type; (void) buffer; (void) reqlen;
    return 0;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize){
    (void) instance; (void) report_id; (void) report_type; (void) buffer; (void) bufsize;
}

static const char* string_desc_arr[] = {
    (const char[]){0x09,0x04}, 
    "X",          
    "MyMacro",       
    "67",                  
};

uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    static uint16_t desc_str[32];
    (void) langid;
    if(index >= sizeof(string_desc_arr)/sizeof(string_desc_arr[0])) return NULL;

    const char* str = string_desc_arr[index];
    uint8_t chr_count = strlen(str);
    for(uint8_t i=0; i<chr_count; i++) desc_str[i+1] = str[i];
    desc_str[0] = (TUSB_DESC_STRING << 8) | (2*chr_count + 2);
    return desc_str;
}
