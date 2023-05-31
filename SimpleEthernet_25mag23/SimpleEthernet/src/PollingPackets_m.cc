//
// Generated file, do not edit! Created by opp_msgtool 6.0 from PollingPackets.msg.
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
#include "PollingPackets_m.h"

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

Register_Class(PollingRequest)

PollingRequest::PollingRequest(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
    this->setByteLength(22);

}

PollingRequest::PollingRequest(const PollingRequest& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

PollingRequest::~PollingRequest()
{
}

PollingRequest& PollingRequest::operator=(const PollingRequest& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void PollingRequest::copy(const PollingRequest& other)
{
    this->flow = other.flow;
    this->requestedFrames = other.requestedFrames;
    this->priority = other.priority;
    this->trxno = other.trxno;
}

void PollingRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->flow);
    doParsimPacking(b,this->requestedFrames);
    doParsimPacking(b,this->priority);
    doParsimPacking(b,this->trxno);
}

void PollingRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->flow);
    doParsimUnpacking(b,this->requestedFrames);
    doParsimUnpacking(b,this->priority);
    doParsimUnpacking(b,this->trxno);
}

const char * PollingRequest::getFlow() const
{
    return this->flow.c_str();
}

void PollingRequest::setFlow(const char * flow)
{
    this->flow = flow;
}

int PollingRequest::getRequestedFrames() const
{
    return this->requestedFrames;
}

void PollingRequest::setRequestedFrames(int requestedFrames)
{
    this->requestedFrames = requestedFrames;
}

long PollingRequest::getPriority() const
{
    return this->priority;
}

void PollingRequest::setPriority(long priority)
{
    this->priority = priority;
}

uint64_t PollingRequest::getTrxno() const
{
    return this->trxno;
}

void PollingRequest::setTrxno(uint64_t trxno)
{
    this->trxno = trxno;
}

class PollingRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_flow,
        FIELD_requestedFrames,
        FIELD_priority,
        FIELD_trxno,
    };
  public:
    PollingRequestDescriptor();
    virtual ~PollingRequestDescriptor();

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

Register_ClassDescriptor(PollingRequestDescriptor)

PollingRequestDescriptor::PollingRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(PollingRequest)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

PollingRequestDescriptor::~PollingRequestDescriptor()
{
    delete[] propertyNames;
}

bool PollingRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PollingRequest *>(obj)!=nullptr;
}

const char **PollingRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PollingRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PollingRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int PollingRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_flow
        FD_ISEDITABLE,    // FIELD_requestedFrames
        FD_ISEDITABLE,    // FIELD_priority
        FD_ISEDITABLE,    // FIELD_trxno
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *PollingRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "flow",
        "requestedFrames",
        "priority",
        "trxno",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int PollingRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "flow") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "requestedFrames") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "priority") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "trxno") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *PollingRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_flow
        "int",    // FIELD_requestedFrames
        "long",    // FIELD_priority
        "uint64_t",    // FIELD_trxno
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **PollingRequestDescriptor::getFieldPropertyNames(int field) const
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

const char *PollingRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PollingRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PollingRequest *pp = omnetpp::fromAnyPtr<PollingRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PollingRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PollingRequest *pp = omnetpp::fromAnyPtr<PollingRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PollingRequest'", field);
    }
}

const char *PollingRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PollingRequest *pp = omnetpp::fromAnyPtr<PollingRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PollingRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PollingRequest *pp = omnetpp::fromAnyPtr<PollingRequest>(object); (void)pp;
    switch (field) {
        case FIELD_flow: return oppstring2string(pp->getFlow());
        case FIELD_requestedFrames: return long2string(pp->getRequestedFrames());
        case FIELD_priority: return long2string(pp->getPriority());
        case FIELD_trxno: return uint642string(pp->getTrxno());
        default: return "";
    }
}

void PollingRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PollingRequest *pp = omnetpp::fromAnyPtr<PollingRequest>(object); (void)pp;
    switch (field) {
        case FIELD_flow: pp->setFlow((value)); break;
        case FIELD_requestedFrames: pp->setRequestedFrames(string2long(value)); break;
        case FIELD_priority: pp->setPriority(string2long(value)); break;
        case FIELD_trxno: pp->setTrxno(string2uint64(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PollingRequest'", field);
    }
}

omnetpp::cValue PollingRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PollingRequest *pp = omnetpp::fromAnyPtr<PollingRequest>(object); (void)pp;
    switch (field) {
        case FIELD_flow: return pp->getFlow();
        case FIELD_requestedFrames: return pp->getRequestedFrames();
        case FIELD_priority: return (omnetpp::intval_t)(pp->getPriority());
        case FIELD_trxno: return (omnetpp::intval_t)(pp->getTrxno());
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PollingRequest' as cValue -- field index out of range?", field);
    }
}

void PollingRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PollingRequest *pp = omnetpp::fromAnyPtr<PollingRequest>(object); (void)pp;
    switch (field) {
        case FIELD_flow: pp->setFlow(value.stringValue()); break;
        case FIELD_requestedFrames: pp->setRequestedFrames(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_priority: pp->setPriority(omnetpp::checked_int_cast<long>(value.intValue())); break;
        case FIELD_trxno: pp->setTrxno(omnetpp::checked_int_cast<uint64_t>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PollingRequest'", field);
    }
}

const char *PollingRequestDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr PollingRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PollingRequest *pp = omnetpp::fromAnyPtr<PollingRequest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PollingRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PollingRequest *pp = omnetpp::fromAnyPtr<PollingRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PollingRequest'", field);
    }
}

Register_Class(PollingData)

PollingData::PollingData(const char *name, short kind) : ::omnetpp::cPacket(name, kind)
{
    this->setByteLength(15);

}

PollingData::PollingData(const PollingData& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

PollingData::~PollingData()
{
}

PollingData& PollingData::operator=(const PollingData& other)
{
    if (this == &other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void PollingData::copy(const PollingData& other)
{
    this->destination = other.destination;
    this->trxno = other.trxno;
    this->last = other.last;
}

void PollingData::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->destination);
    doParsimPacking(b,this->trxno);
    doParsimPacking(b,this->last);
}

void PollingData::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->destination);
    doParsimUnpacking(b,this->trxno);
    doParsimUnpacking(b,this->last);
}

const char * PollingData::getDestination() const
{
    return this->destination.c_str();
}

void PollingData::setDestination(const char * destination)
{
    this->destination = destination;
}

uint64_t PollingData::getTrxno() const
{
    return this->trxno;
}

void PollingData::setTrxno(uint64_t trxno)
{
    this->trxno = trxno;
}

bool PollingData::getLast() const
{
    return this->last;
}

void PollingData::setLast(bool last)
{
    this->last = last;
}

class PollingDataDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_destination,
        FIELD_trxno,
        FIELD_last,
    };
  public:
    PollingDataDescriptor();
    virtual ~PollingDataDescriptor();

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

Register_ClassDescriptor(PollingDataDescriptor)

PollingDataDescriptor::PollingDataDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(PollingData)), "omnetpp::cPacket")
{
    propertyNames = nullptr;
}

PollingDataDescriptor::~PollingDataDescriptor()
{
    delete[] propertyNames;
}

bool PollingDataDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PollingData *>(obj)!=nullptr;
}

const char **PollingDataDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PollingDataDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PollingDataDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int PollingDataDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_destination
        FD_ISEDITABLE,    // FIELD_trxno
        FD_ISEDITABLE,    // FIELD_last
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *PollingDataDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "destination",
        "trxno",
        "last",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int PollingDataDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "destination") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "trxno") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "last") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *PollingDataDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_destination
        "uint64_t",    // FIELD_trxno
        "bool",    // FIELD_last
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **PollingDataDescriptor::getFieldPropertyNames(int field) const
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

const char *PollingDataDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int PollingDataDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PollingData *pp = omnetpp::fromAnyPtr<PollingData>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PollingDataDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PollingData *pp = omnetpp::fromAnyPtr<PollingData>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PollingData'", field);
    }
}

const char *PollingDataDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PollingData *pp = omnetpp::fromAnyPtr<PollingData>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PollingDataDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PollingData *pp = omnetpp::fromAnyPtr<PollingData>(object); (void)pp;
    switch (field) {
        case FIELD_destination: return oppstring2string(pp->getDestination());
        case FIELD_trxno: return uint642string(pp->getTrxno());
        case FIELD_last: return bool2string(pp->getLast());
        default: return "";
    }
}

void PollingDataDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PollingData *pp = omnetpp::fromAnyPtr<PollingData>(object); (void)pp;
    switch (field) {
        case FIELD_destination: pp->setDestination((value)); break;
        case FIELD_trxno: pp->setTrxno(string2uint64(value)); break;
        case FIELD_last: pp->setLast(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PollingData'", field);
    }
}

omnetpp::cValue PollingDataDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PollingData *pp = omnetpp::fromAnyPtr<PollingData>(object); (void)pp;
    switch (field) {
        case FIELD_destination: return pp->getDestination();
        case FIELD_trxno: return (omnetpp::intval_t)(pp->getTrxno());
        case FIELD_last: return pp->getLast();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PollingData' as cValue -- field index out of range?", field);
    }
}

void PollingDataDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PollingData *pp = omnetpp::fromAnyPtr<PollingData>(object); (void)pp;
    switch (field) {
        case FIELD_destination: pp->setDestination(value.stringValue()); break;
        case FIELD_trxno: pp->setTrxno(omnetpp::checked_int_cast<uint64_t>(value.intValue())); break;
        case FIELD_last: pp->setLast(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PollingData'", field);
    }
}

const char *PollingDataDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr PollingDataDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PollingData *pp = omnetpp::fromAnyPtr<PollingData>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PollingDataDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PollingData *pp = omnetpp::fromAnyPtr<PollingData>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PollingData'", field);
    }
}

FlowTableEntry::FlowTableEntry()
{
}

void __doPacking(omnetpp::cCommBuffer *b, const FlowTableEntry& a)
{
    doParsimPacking(b,a.flow);
    doParsimPacking(b,a.addr);
    doParsimPacking(b,a.burst);
    doParsimPacking(b,a.period);
    doParsimPacking(b,a.deadline);
}

void __doUnpacking(omnetpp::cCommBuffer *b, FlowTableEntry& a)
{
    doParsimUnpacking(b,a.flow);
    doParsimUnpacking(b,a.addr);
    doParsimUnpacking(b,a.burst);
    doParsimUnpacking(b,a.period);
    doParsimUnpacking(b,a.deadline);
}

class FlowTableEntryDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_flow,
        FIELD_addr,
        FIELD_burst,
        FIELD_period,
        FIELD_deadline,
    };
  public:
    FlowTableEntryDescriptor();
    virtual ~FlowTableEntryDescriptor();

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

Register_ClassDescriptor(FlowTableEntryDescriptor)

FlowTableEntryDescriptor::FlowTableEntryDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(FlowTableEntry)), "")
{
    propertyNames = nullptr;
}

FlowTableEntryDescriptor::~FlowTableEntryDescriptor()
{
    delete[] propertyNames;
}

bool FlowTableEntryDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FlowTableEntry *>(obj)!=nullptr;
}

const char **FlowTableEntryDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *FlowTableEntryDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int FlowTableEntryDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int FlowTableEntryDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_flow
        FD_ISEDITABLE,    // FIELD_addr
        FD_ISEDITABLE,    // FIELD_burst
        FD_ISEDITABLE,    // FIELD_period
        FD_ISEDITABLE,    // FIELD_deadline
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *FlowTableEntryDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "flow",
        "addr",
        "burst",
        "period",
        "deadline",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int FlowTableEntryDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "flow") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "addr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "burst") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "period") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "deadline") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *FlowTableEntryDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_flow
        "string",    // FIELD_addr
        "int",    // FIELD_burst
        "omnetpp::simtime_t",    // FIELD_period
        "omnetpp::simtime_t",    // FIELD_deadline
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **FlowTableEntryDescriptor::getFieldPropertyNames(int field) const
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

const char *FlowTableEntryDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int FlowTableEntryDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    FlowTableEntry *pp = omnetpp::fromAnyPtr<FlowTableEntry>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void FlowTableEntryDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowTableEntry *pp = omnetpp::fromAnyPtr<FlowTableEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'FlowTableEntry'", field);
    }
}

const char *FlowTableEntryDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    FlowTableEntry *pp = omnetpp::fromAnyPtr<FlowTableEntry>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlowTableEntryDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    FlowTableEntry *pp = omnetpp::fromAnyPtr<FlowTableEntry>(object); (void)pp;
    switch (field) {
        case FIELD_flow: return oppstring2string(pp->flow);
        case FIELD_addr: return oppstring2string(pp->addr);
        case FIELD_burst: return long2string(pp->burst);
        case FIELD_period: return simtime2string(pp->period);
        case FIELD_deadline: return simtime2string(pp->deadline);
        default: return "";
    }
}

void FlowTableEntryDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowTableEntry *pp = omnetpp::fromAnyPtr<FlowTableEntry>(object); (void)pp;
    switch (field) {
        case FIELD_flow: pp->flow = (value); break;
        case FIELD_addr: pp->addr = (value); break;
        case FIELD_burst: pp->burst = string2long(value); break;
        case FIELD_period: pp->period = string2simtime(value); break;
        case FIELD_deadline: pp->deadline = string2simtime(value); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowTableEntry'", field);
    }
}

omnetpp::cValue FlowTableEntryDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    FlowTableEntry *pp = omnetpp::fromAnyPtr<FlowTableEntry>(object); (void)pp;
    switch (field) {
        case FIELD_flow: return pp->flow;
        case FIELD_addr: return pp->addr;
        case FIELD_burst: return pp->burst;
        case FIELD_period: return pp->period.dbl();
        case FIELD_deadline: return pp->deadline.dbl();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'FlowTableEntry' as cValue -- field index out of range?", field);
    }
}

void FlowTableEntryDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowTableEntry *pp = omnetpp::fromAnyPtr<FlowTableEntry>(object); (void)pp;
    switch (field) {
        case FIELD_flow: pp->flow = value.stringValue(); break;
        case FIELD_addr: pp->addr = value.stringValue(); break;
        case FIELD_burst: pp->burst = omnetpp::checked_int_cast<int>(value.intValue()); break;
        case FIELD_period: pp->period = value.doubleValue(); break;
        case FIELD_deadline: pp->deadline = value.doubleValue(); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowTableEntry'", field);
    }
}

const char *FlowTableEntryDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr FlowTableEntryDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    FlowTableEntry *pp = omnetpp::fromAnyPtr<FlowTableEntry>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void FlowTableEntryDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowTableEntry *pp = omnetpp::fromAnyPtr<FlowTableEntry>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowTableEntry'", field);
    }
}

Register_Class(FlowTableParameters)

FlowTableParameters::FlowTableParameters(const char *name) : ::omnetpp::cOwnedObject(name)
{
}

FlowTableParameters::FlowTableParameters(const FlowTableParameters& other) : ::omnetpp::cOwnedObject(other)
{
    copy(other);
}

FlowTableParameters::~FlowTableParameters()
{
    delete [] this->flows;
}

FlowTableParameters& FlowTableParameters::operator=(const FlowTableParameters& other)
{
    if (this == &other) return *this;
    ::omnetpp::cOwnedObject::operator=(other);
    copy(other);
    return *this;
}

void FlowTableParameters::copy(const FlowTableParameters& other)
{
    delete [] this->flows;
    this->flows = (other.flows_arraysize==0) ? nullptr : new FlowTableEntry[other.flows_arraysize];
    flows_arraysize = other.flows_arraysize;
    for (size_t i = 0; i < flows_arraysize; i++) {
        this->flows[i] = other.flows[i];
    }
}

void FlowTableParameters::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cOwnedObject::parsimPack(b);
    b->pack(flows_arraysize);
    doParsimArrayPacking(b,this->flows,flows_arraysize);
}

void FlowTableParameters::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cOwnedObject::parsimUnpack(b);
    delete [] this->flows;
    b->unpack(flows_arraysize);
    if (flows_arraysize == 0) {
        this->flows = nullptr;
    } else {
        this->flows = new FlowTableEntry[flows_arraysize];
        doParsimArrayUnpacking(b,this->flows,flows_arraysize);
    }
}

size_t FlowTableParameters::getFlowsArraySize() const
{
    return flows_arraysize;
}

const FlowTableEntry& FlowTableParameters::getFlows(size_t k) const
{
    if (k >= flows_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)flows_arraysize, (unsigned long)k);
    return this->flows[k];
}

void FlowTableParameters::setFlowsArraySize(size_t newSize)
{
    FlowTableEntry *flows2 = (newSize==0) ? nullptr : new FlowTableEntry[newSize];
    size_t minSize = flows_arraysize < newSize ? flows_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        flows2[i] = this->flows[i];
    delete [] this->flows;
    this->flows = flows2;
    flows_arraysize = newSize;
}

void FlowTableParameters::setFlows(size_t k, const FlowTableEntry& flows)
{
    if (k >= flows_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)flows_arraysize, (unsigned long)k);
    this->flows[k] = flows;
}

void FlowTableParameters::insertFlows(size_t k, const FlowTableEntry& flows)
{
    if (k > flows_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)flows_arraysize, (unsigned long)k);
    size_t newSize = flows_arraysize + 1;
    FlowTableEntry *flows2 = new FlowTableEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        flows2[i] = this->flows[i];
    flows2[k] = flows;
    for (i = k + 1; i < newSize; i++)
        flows2[i] = this->flows[i-1];
    delete [] this->flows;
    this->flows = flows2;
    flows_arraysize = newSize;
}

void FlowTableParameters::appendFlows(const FlowTableEntry& flows)
{
    insertFlows(flows_arraysize, flows);
}

void FlowTableParameters::eraseFlows(size_t k)
{
    if (k >= flows_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)flows_arraysize, (unsigned long)k);
    size_t newSize = flows_arraysize - 1;
    FlowTableEntry *flows2 = (newSize == 0) ? nullptr : new FlowTableEntry[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        flows2[i] = this->flows[i];
    for (i = k; i < newSize; i++)
        flows2[i] = this->flows[i+1];
    delete [] this->flows;
    this->flows = flows2;
    flows_arraysize = newSize;
}

class FlowTableParametersDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_flows,
    };
  public:
    FlowTableParametersDescriptor();
    virtual ~FlowTableParametersDescriptor();

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

Register_ClassDescriptor(FlowTableParametersDescriptor)

FlowTableParametersDescriptor::FlowTableParametersDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(FlowTableParameters)), "omnetpp::cOwnedObject")
{
    propertyNames = nullptr;
}

FlowTableParametersDescriptor::~FlowTableParametersDescriptor()
{
    delete[] propertyNames;
}

bool FlowTableParametersDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FlowTableParameters *>(obj)!=nullptr;
}

const char **FlowTableParametersDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *FlowTableParametersDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int FlowTableParametersDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int FlowTableParametersDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISARRAY | FD_ISCOMPOUND | FD_ISRESIZABLE,    // FIELD_flows
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *FlowTableParametersDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "flows",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int FlowTableParametersDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "flows") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *FlowTableParametersDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "FlowTableEntry",    // FIELD_flows
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **FlowTableParametersDescriptor::getFieldPropertyNames(int field) const
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

const char *FlowTableParametersDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int FlowTableParametersDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    FlowTableParameters *pp = omnetpp::fromAnyPtr<FlowTableParameters>(object); (void)pp;
    switch (field) {
        case FIELD_flows: return pp->getFlowsArraySize();
        default: return 0;
    }
}

void FlowTableParametersDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowTableParameters *pp = omnetpp::fromAnyPtr<FlowTableParameters>(object); (void)pp;
    switch (field) {
        case FIELD_flows: pp->setFlowsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'FlowTableParameters'", field);
    }
}

const char *FlowTableParametersDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    FlowTableParameters *pp = omnetpp::fromAnyPtr<FlowTableParameters>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FlowTableParametersDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    FlowTableParameters *pp = omnetpp::fromAnyPtr<FlowTableParameters>(object); (void)pp;
    switch (field) {
        case FIELD_flows: return "";
        default: return "";
    }
}

void FlowTableParametersDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowTableParameters *pp = omnetpp::fromAnyPtr<FlowTableParameters>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowTableParameters'", field);
    }
}

omnetpp::cValue FlowTableParametersDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    FlowTableParameters *pp = omnetpp::fromAnyPtr<FlowTableParameters>(object); (void)pp;
    switch (field) {
        case FIELD_flows: return omnetpp::toAnyPtr(&pp->getFlows(i)); break;
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'FlowTableParameters' as cValue -- field index out of range?", field);
    }
}

void FlowTableParametersDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowTableParameters *pp = omnetpp::fromAnyPtr<FlowTableParameters>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowTableParameters'", field);
    }
}

const char *FlowTableParametersDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        case FIELD_flows: return omnetpp::opp_typename(typeid(FlowTableEntry));
        default: return nullptr;
    };
}

omnetpp::any_ptr FlowTableParametersDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    FlowTableParameters *pp = omnetpp::fromAnyPtr<FlowTableParameters>(object); (void)pp;
    switch (field) {
        case FIELD_flows: return omnetpp::toAnyPtr(&pp->getFlows(i)); break;
        default: return omnetpp::any_ptr(nullptr);
    }
}

void FlowTableParametersDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    FlowTableParameters *pp = omnetpp::fromAnyPtr<FlowTableParameters>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'FlowTableParameters'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

