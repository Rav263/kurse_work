#define MEMORY_SIZE         (0x80000)
#define METADATA_SIZE       (0x20)
#define METADATA_START      (MEMORY_SIZE-METADATA_SIZE)
#define METADATA_HSIZE      (METADATA_START+2)
#define METADATA_HSTART     (METADATA_START+4)
#define METADATA_INPORT     (METADATA_START+6)
#define METADATA_TIMESTAMP  (METADATA_START+7)
#define METADATA_PORTMASK   (METADATA_START+8)
#define HEADER_SIZE         (0x80)      
#define HEADER_START        (METADATA_START-HEADER_SIZE)

#define PORTMASK_SIZE       (0x40)

#define PORTMASK_SIZE       (0x40)
#define MACADDR_SIZE        (0x30)

#define BCAST_MACADDR       0xffffffffffff

#define PHYSICAL_PORTS 0xffffff

end
//#define CONTROL_PORT_MSK    (1<<63)