#ifndef NumericProvider_hpp
#define NumericProvider_hpp


//--------------------------------------------------------------------------
//                            class NumericProvider

template<typename T>
class NumericProvider {
    template<typename U>
    friend class NumericProvider;
    
    template<typename U>
    using enable_if_original_t = typename std::enable_if<GT::isOriginalType<U>::value>::type;
    
protected:
    TRACE_STRING_SAVE____(std::string id);
    TRACE_STRING_SAVE____(std::string  calcExpres);
    T data;
    
public:
    template<typename... Args>
    NumericProvider(Args... args)
    : data(args...) {
    }
    
    NumericProvider(const char* id = GuardConfig::defaultId)
    : data()
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId(id));
    }
    
    template<typename U>
    NumericProvider(const U& data, enable_if_original_t<U>* = 0)
    : data(data)
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId());
    }
    
    template<typename U>
    NumericProvider(const U& data, bool)
    : data(data)
    {
    }
    
    
    NumericProvider(const NumericProvider& data)
    : data(data.data)
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    template<typename U>
    NumericProvider(const NumericProvider<U>& data)
    : data(data.data) {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    // const rvalue constructor
    template<typename U>
    NumericProvider(const U&& data, enable_if_original_t<U>* = 0)
    : data(std::forward<const U>(data))
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId());
    }
    
    
    NumericProvider(const NumericProvider&& data)
    : data(std::forward<const T>(data.data))
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    template<typename U>
    NumericProvider(const NumericProvider<U>&& data)
    : data(std::forward<const U>(data.data)) {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    // rvalue constructor
    template<typename U>
    NumericProvider(U&& data, enable_if_original_t<U>* = 0)
    : data(std::forward<U>(data))
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewId());
    }
    
    
    NumericProvider(NumericProvider&& data)
    : data(std::forward<T>(data.data))
    {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    template<typename U>
    NumericProvider(NumericProvider<U>&& data)
    : data(std::forward<U>(data.data)) {
        TRACE_STRING_SAVE____(this->id = GT::GetNewIdByIncreaseId(data.id));
    }
    
    T& Data() {
        return data;
    }
    
    const T& Data() const {
        return data;
    }
    
    const std::string& Id() const {
        TRACE_STRING_SAVE____(return id);
        return GuardConfig::defaultIdStr;
    }
    
    const std::string CalcString() const {
        if(GuardConfig::GuardConfig::_OUT_PUT_EXPRES_SWITCH == false) return "";
        TRACE_STRING_SAVE____(if(this->calcExpres != "") return this->calcExpres);
        if(GuardConfig::_OUT_PUT_EXPRES_ID_OR_NUM_SWITCH == true) {
            return this->Id();
        } else {
            return GT::NumericToString(this->Data());
        }
    }
    
    void setExpress(const std::string& express) const {
        TRACE_STRING_SAVE____(if(GuardConfig::_OUT_PUT_EXPRES_SWITCH) const_cast<std::string&>(this->calcExpres) = express);
    }
    
    void OutputArray() const {}
};

#endif /* NumericProvider_hpp */
