//
// Generated file, do not edit! Created by opp_msgtool 6.0 from EthernetFrames.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "EthernetFrames_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(EthernetFrame)

EthernetFrame::EthernetFrame(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
    this->setByteLength(26);

}

EthernetFrame::EthernetFrame(const EthernetFrame& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

EthernetFrame::~EthernetFrame()
{
}

EthernetFrame& EthernetFrame::operator=(const EthernetFrame& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void EthernetFrame::copy(const EthernetFrame& other)
{
    this->dst = other.dst;
    this->src = other.src;
    this->ethertype = other.ethertype;
}

void EthernetFrame::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->dst);
    doParsimPacking(b,this->src);
    doParsimPacking(b,this->ethertype);
}

void EthernetFrame::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->dst);
    doParsimUnpacking(b,this->src);
    doParsimUnpacking(b,this->ethertype);
}

const char * EthernetFrame::getDst() const
{
    return this->dst.c_str();
}

void EthernetFrame::setDst(const char * dst)
{
    this->dst = dst;
}

const char * EthernetFrame::getSrc() const
{
    return this->src.c_str();
}

void EthernetFrame::setSrc(const char * src)
{
    this->src = src;
}

int EthernetFrame::getEthertype() const
{
    return this->ethertype;
}

void EthernetFrame::setEthertype(int ethertype)
{
    this->ethertype = ethertype;
}

class EthernetFrameDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_dst,
        FIELD_src,
        FIELD_ethertype,
    };
  public:
    EthernetFrameDescriptor();
    virtual ~EthernetFrameDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(EthernetFrameDescriptor)

EthernetFrameDescriptor::EthernetFrameDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(EthernetFrame)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

EthernetFrameDescriptor::~EthernetFrameDescriptor()
{
    delete[] propertyNames;
}

bool EthernetFrameDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<EthernetFrame *>(obj)!=nullptr;
}

const char **EthernetFrameDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *EthernetFrameDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int EthernetFrameDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int EthernetFrameDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_dst
        FD_ISEDITABLE,    // FIELD_src
        FD_ISEDITABLE,    // FIELD_ethertype
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *EthernetFrameDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "dst",
        "src",
        "ethertype",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int EthernetFrameDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "dst") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "src") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "ethertype") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *EthernetFrameDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_dst
        "string",    // FIELD_src
        "int",    // FIELD_ethertype
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **EthernetFrameDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *EthernetFrameDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int EthernetFrameDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    EthernetFrame *pp = omnetpp::fromAnyPtr<EthernetFrame>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void EthernetFrameDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetFrame *pp = omnetpp::fromAnyPtr<EthernetFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'EthernetFrame'", field);
    }
}

const char *EthernetFrameDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetFrame *pp = omnetpp::fromAnyPtr<EthernetFrame>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string EthernetFrameDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetFrame *pp = omnetpp::fromAnyPtr<EthernetFrame>(object); (void)pp;
    switch (field) {
        case FIELD_dst: return oppstring2string(pp->getDst());
        case FIELD_src: return oppstring2string(pp->getSrc());
        case FIELD_ethertype: return long2string(pp->getEthertype());
        default: return "";
    }
}

void EthernetFrameDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetFrame *pp = omnetpp::fromAnyPtr<EthernetFrame>(object); (void)pp;
    switch (field) {
        case FIELD_dst: pp->setDst((value)); break;
        case FIELD_src: pp->setSrc((value)); break;
        case FIELD_ethertype: pp->setEthertype(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetFrame'", field);
    }
}

omnetpp::cValue EthernetFrameDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    EthernetFrame *pp = omnetpp::fromAnyPtr<EthernetFrame>(object); (void)pp;
    switch (field) {
        case FIELD_dst: return pp->getDst();
        case FIELD_src: return pp->getSrc();
        case FIELD_ethertype: return pp->getEthertype();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'EthernetFrame' as cValue -- field index out of range?", field);
    }
}

void EthernetFrameDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetFrame *pp = omnetpp::fromAnyPtr<EthernetFrame>(object); (void)pp;
    switch (field) {
        case FIELD_dst: pp->setDst(value.stringValue()); break;
        case FIELD_src: pp->setSrc(value.stringValue()); break;
        case FIELD_ethertype: pp->setEthertype(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetFrame'", field);
    }
}

const char *EthernetFrameDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr EthernetFrameDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    EthernetFrame *pp = omnetpp::fromAnyPtr<EthernetFrame>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void EthernetFrameDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    EthernetFrame *pp = omnetpp::fromAnyPtr<EthernetFrame>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'EthernetFrame'", field);
    }
}

RelayTableEntry::RelayTableEntry()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const RelayTableEntry& a)
{
    doParsimPacking(b,a.addr);
    doParsimPacking(b,a.port);
}

void __doUnpacking(omnetpp::cCommBuffer *b, RelayTableEntry& a)
{
    doParsimUnpacking(b,a.addr);
    doParsimUnpacking(b,a.port);
}

class RelayTableEntryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_addr,
        FIELD_port,
    };
  public:
    RelayTableEntryDescriptor();
    virtual ~RelayTableEntryDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(RelayTableEntryDescriptor)

RelayTableEntryDescriptor::RelayTableEntryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(RelayTableEntry)), "")
{
    propertyNames = nullptr;
}

RelayTableEntryDescriptor::~RelayTableEntryDescriptor()
{
    delete[] propertyNames;
}

bool RelayTableEntryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RelayTableEntry *>(obj)!=nullptr;
}

const char **RelayTableEntryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RelayTableEntryDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RelayTableEntryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 2+base->getFieldCount() : 2;
}

unsigned int RelayTableEntryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_addr
        FD_ISEDITABLE,    // FIELD_port
    };
    return (field >= 0 && field < 2) ? fieldTypeFlags[field] : 0;
}

const char *RelayTableEntryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "addr",
        "port",
    };
    return (field >= 0 && field < 2) ? fieldNames[field] : nullptr;
}

int RelayTableEntryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "addr") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "port") == 0) return baseIndex + 1;
    return base ? base->findField(fieldName) : -1;
}

const char *RelayTableEntryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_addr
        "int",    // FIELD_port
    };
    return (field >= 0 && field < 2) ? fieldTypeStrings[field] : nullptr;
}

const char **RelayTableEntryDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RelayTableEntryDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RelayTableEntryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RelayTableEntry *pp = omnetpp::fromAnyPtr<RelayTableEntry>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RelayTableEntryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RelayTableEntry *pp = omnetpp::fromAnyPtr<RelayTableEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RelayTableEntry'", field);
    }
}

const char *RelayTableEntryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RelayTableEntry *pp = omnetpp::fromAnyPtr<RelayTableEntry>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RelayTableEntryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RelayTableEntry *pp = omnetpp::fromAnyPtr<RelayTableEntry>(object); (void)pp;
    switch (field) {
        case FIELD_addr: return oppstring2string(pp->addr);
        case FIELD_port: return long2string(pp->port);
        default: return "";
    }
}

void RelayTableEntryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RelayTableEntry *pp = omnetpp::fromAnyPtr<RelayTableEntry>(object); (void)pp;
    switch (field) {
        case FIELD_addr: pp->addr = (value); break;
        case FIELD_port: pp->port = string2long(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RelayTableEntry'", field);
    }
}

omnetpp::cValue RelayTableEntryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RelayTableEntry *pp = omnetpp::fromAnyPtr<RelayTableEntry>(object); (void)pp;
    switch (field) {
        case FIELD_addr: return pp->addr;
        case FIELD_port: return pp->port;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RelayTableEntry' as cValue -- field index out of range?", field);
    }
}

void RelayTableEntryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RelayTableEntry *pp = omnetpp::fromAnyPtr<RelayTableEntry>(object); (void)pp;
    switch (field) {
        case FIELD_addr: pp->addr = value.stringValue(); break;
        case FIELD_port: pp->port = omnetpp::checked_int_cast<int>(value.intValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RelayTableEntry'", field);
    }
}

const char *RelayTableEntryDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr RelayTableEntryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RelayTableEntry *pp = omnetpp::fromAnyPtr<RelayTableEntry>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RelayTableEntryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RelayTableEntry *pp = omnetpp::fromAnyPtr<RelayTableEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RelayTableEntry'", field);
    }
}

Register_Class(StaticRelayEntries)

StaticRelayEntries::StaticRelayEntries(const char *name) : ::omnetpp::cOwnedObject(name)
{
}

StaticRelayEntries::StaticRelayEntries(const StaticRelayEntries& other) : ::omnetpp::cOwnedObject(other)
{
    copy(other);
}

StaticRelayEntries::~StaticRelayEntries()
{
    delete [] this->entries;
}

StaticRelayEntries& StaticRelayEntries::operator=(const StaticRelayEntries& other)
{
    if (this == &other) return *this;
    ::omnetpp::cOwnedObject::operator=(other);
    copy(other);
    return *this;
}

void StaticRelayEntries::copy(const StaticRelayEntries& other)
{
    delete [] this->entries;
    this->entries = (other.entries_arraysize==0) ? nullptr : new RelayTableEntry[other.entries_arraysize];
    entries_arraysize = other.entries_arraysize;
    for (size_t i = 0; i < entries_arraysize; i++) {
        this->entries[i] = other.entries[i];
    }
}

void StaticRelayEntries::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cOwnedObject::parsimPack(b);
    b->pack(entries_arraysize);
    doParsimArrayPacking(b,this->entries,entries_arraysize);
}

void StaticRelayEntries::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cOwnedObject::parsimUnpack(b);
    delete [] this->entries;
    b->unpack(entries_arraysize);
    if (entries_arraysize == 0) {
        this->entries = nullptr;
    } else {
        this->entries = new RelayTableEntry[entries_arraysize];
        doParsimArrayUnpacking(b,this->entries,entries_arraysize);
    }
}

size_t StaticRelayEntries::getEntriesArraySize() const
{
    return entries_arraysize;
}

const RelayTableEntry& StaticRelayEntries::getEntries(size_t k) const
{
    if (k >= entries_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)entries_arraysize, (unsigned long)k);
    return this->entries[k];
}

void StaticRelayEntries::setEntriesArraySize(size_t newSize)
{
    RelayTableEntry *entries2 = (newSize==0) ? nullptr : new RelayTableEntry[newSize];
    size_t minSize = entries_arraysize < newSize ? entries_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        entries2[i] = this->entries[i];
    delete [] this->entries;
    this->entries = entries2;
    entries_arraysize = newSize;
}

void StaticRelayEntries::setEntries(size_t k, const RelayTableEntry& entries)
{
    if (k >= entries_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)entries_arraysize, (unsigned long)k);
    this->entries[k] = entries;
}

void StaticRelayEntries::insertEntries(size_t k, const RelayTableEntry& entries)
{
    if (k > entries_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)entries_arraysize, (unsigned long)k);
    size_t newSize = entries_arraysize + 1;
    RelayTableEntry *entries2 = new RelayTableEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        entries2[i] = this->entries[i];
    entries2[k] = entries;
    for (i = k + 1; i < newSize; i++)
        entries2[i] = this->entries[i-1];
    delete [] this->entries;
    this->entries = entries2;
    entries_arraysize = newSize;
}

void StaticRelayEntries::appendEntries(const RelayTableEntry& entries)
{
    insertEntries(entries_arraysize, entries);
}

void StaticRelayEntries::eraseEntries(size_t k)
{
    if (k >= entries_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)entries_arraysize, (unsigned long)k);
    size_t newSize = entries_arraysize - 1;
    RelayTableEntry *entries2 = (newSize == 0) ? nullptr : new RelayTableEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        entries2[i] = this->entries[i];
    for (i = k; i < newSize; i++)
        entries2[i] = this->entries[i+1];
    delete [] this->entries;
    this->entries = entries2;
    entries_arraysize = newSize;
}

class StaticRelayEntriesDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_entries,
    };
  public:
    StaticRelayEntriesDescriptor();
    virtual ~StaticRelayEntriesDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(StaticRelayEntriesDescriptor)

StaticRelayEntriesDescriptor::StaticRelayEntriesDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(StaticRelayEntries)), "omnetpp::cOwnedObject")
{
    propertyNames = nullptr;
}

StaticRelayEntriesDescriptor::~StaticRelayEntriesDescriptor()
{
    delete[] propertyNames;
}

bool StaticRelayEntriesDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<StaticRelayEntries *>(obj)!=nullptr;
}

const char **StaticRelayEntriesDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *StaticRelayEntriesDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int StaticRelayEntriesDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int StaticRelayEntriesDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_entries
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *StaticRelayEntriesDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "entries",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int StaticRelayEntriesDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "entries") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *StaticRelayEntriesDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "RelayTableEntry",    // FIELD_entries
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **StaticRelayEntriesDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *StaticRelayEntriesDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int StaticRelayEntriesDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    StaticRelayEntries *pp = omnetpp::fromAnyPtr<StaticRelayEntries>(object); (void)pp;
    switch (field) {
        case FIELD_entries: return pp->getEntriesArraySize();
        default: return 0;
    }
}

void StaticRelayEntriesDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    StaticRelayEntries *pp = omnetpp::fromAnyPtr<StaticRelayEntries>(object); (void)pp;
    switch (field) {
        case FIELD_entries: pp->setEntriesArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'StaticRelayEntries'", field);
    }
}

const char *StaticRelayEntriesDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    StaticRelayEntries *pp = omnetpp::fromAnyPtr<StaticRelayEntries>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string StaticRelayEntriesDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    StaticRelayEntries *pp = omnetpp::fromAnyPtr<StaticRelayEntries>(object); (void)pp;
    switch (field) {
        case FIELD_entries: return "";
        default: return "";
    }
}

void StaticRelayEntriesDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    StaticRelayEntries *pp = omnetpp::fromAnyPtr<StaticRelayEntries>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'StaticRelayEntries'", field);
    }
}

omnetpp::cValue StaticRelayEntriesDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    StaticRelayEntries *pp = omnetpp::fromAnyPtr<StaticRelayEntries>(object); (void)pp;
    switch (field) {
        case FIELD_entries: return omnetpp::toAnyPtr(&pp->getEntries(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'StaticRelayEntries' as cValue -- field index out of range?", field);
    }
}

void StaticRelayEntriesDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    StaticRelayEntries *pp = omnetpp::fromAnyPtr<StaticRelayEntries>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'StaticRelayEntries'", field);
    }
}

const char *StaticRelayEntriesDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_entries: return omnetpp::opp_typename(typeid(RelayTableEntry));
        default: return nullptr;
    };
}

omnetpp::any_ptr StaticRelayEntriesDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    StaticRelayEntries *pp = omnetpp::fromAnyPtr<StaticRelayEntries>(object); (void)pp;
    switch (field) {
        case FIELD_entries: return omnetpp::toAnyPtr(&pp->getEntries(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void StaticRelayEntriesDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    StaticRelayEntries *pp = omnetpp::fromAnyPtr<StaticRelayEntries>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'StaticRelayEntries'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

