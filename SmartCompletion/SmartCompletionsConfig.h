#ifndef SMARTCOMPLETIONSCONFIG_H
#define SMARTCOMPLETIONSCONFIG_H

#include "cl_config.h"
class SmartCompletionsConfig : public clConfigItem
{
public:
    virtual void FromJSON(const JSONElement& json);
    virtual JSONElement ToJSON() const;

    enum eOptions {
        kEnabled = (1 << 0),
    };

protected:
    size_t m_flags;

public:
    SmartCompletionsConfig();
    virtual ~SmartCompletionsConfig();

    SmartCompletionsConfig& Load();
    SmartCompletionsConfig& Save();

    bool IsEnabled() const { return m_flags & kEnabled; }
    void SetEnabled(bool b) { b ? m_flags |= kEnabled : m_flags &= ~kEnabled; }
};

#endif // SMARTCOMPLETIONSCONFIG_H