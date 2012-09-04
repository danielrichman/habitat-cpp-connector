/* Copyright 2011 (C) Daniel Richman. License: GNU GPL 3; see COPYING. */

#include "habitat/Extractor.h"
#include <vector>
#include "habitat/EZ.h"

namespace habitat {

void ExtractorManager::add(Extractor &e)
{
    EZ::MutexLock lock(mutex);

    extractors.push_back(&e);
    e.mgr = this;
}

void ExtractorManager::skipped(int n)
{
    EZ::MutexLock lock(mutex);

    vector<Extractor *>::iterator it;

    for (it = extractors.begin(); it != extractors.end(); it++)
        (*it)->skipped(n);
}

void ExtractorManager::push(char b, enum push_flags flags)
{
    EZ::MutexLock lock(mutex);

    vector<Extractor *>::iterator it;

    for (it = extractors.begin(); it != extractors.end(); it++)
        (*it)->push(b, flags);
}

void ExtractorManager::payload(const Json::Value *set)
{
    EZ::MutexLock lock(mutex);
    current_payload = set;
}

const Json::Value *ExtractorManager::payload()
{
    EZ::MutexLock lock(mutex);
    return current_payload;
}

} /* namespace habitat */
