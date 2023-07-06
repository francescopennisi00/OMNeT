packet EthernetFrame {
    string dst;
    string src;
    int ethertype;
    byteLength = 26;
};

struct RelayTableEntry {
    string addr;
    int port;
};

class StaticRelayEntries extends cOwnedObject {
    RelayTableEntry entries[];
};