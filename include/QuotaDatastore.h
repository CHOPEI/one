/* -------------------------------------------------------------------------- */
/* Copyright 2002-2012, OpenNebula Project Leads (OpenNebula.org)             */
/*                                                                            */
/* Licensed under the Apache License, Version 2.0 (the "License"); you may    */
/* not use this file except in compliance with the License. You may obtain    */
/* a copy of the License at                                                   */
/*                                                                            */
/* http://www.apache.org/licenses/LICENSE-2.0                                 */
/*                                                                            */
/* Unless required by applicable law or agreed to in writing, software        */
/* distributed under the License is distributed on an "AS IS" BASIS,          */
/* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.   */
/* See the License for the specific language governing permissions and        */
/* limitations under the License.                                             */
/* -------------------------------------------------------------------------- */

#ifndef QUOTA_DATASTORE_H_
#define QUOTA_DATASTORE_H_

#include "Quota.h"

/**
 *  DataStore Quotas, defined as:
 *    DATASTORE = [
 *        NAME   = <Name of the datastore>
 *        IMAGES = <Max. number of images allowed in the datastore>
 *        SIZE   = <Max. number of MB used in the datastore>
 *        IMAGES_USED = Current number of images in the datastore
 *        SIZE_USED   = Current storage capacity un the datastore
 *    ]
 *
 *   0 = unlimited, default if missing
 */

class QuotaDatastore :  public Quota
{
public:
    
    QuotaDatastore():Quota("DATASTORE_QUOTA"){};

    ~QuotaDatastore(){};

    /**
     *  Check if the resource allocation will exceed the quota limits. If not 
     *  the usage counters are updated
     *    @param tmpl template for the resource
     *    @param error string 
     *    @return true if the operation can be performed
     */
    bool check_add(Template* tmpl,  string& error);

    /**
     *  Decrement usage counters when deallocating image
     *    @param tmpl template for the resource
     */
    void del(Template* tmpl);

protected:

    /** 
     *  Sets new limit values for the quota
     *    @param quota to be updated
     *    @param va attribute with the new limits
     *    @return 0 on success or -1 if wrong limits
     */
    int update_limits(Attribute * quota, Attribute * va);

    /**
     *  Creates an empty quota based on the given attribute. The attribute va
     *  contains the limits for the quota.
     *    @param va limits for the new quota if 0 limits will be 0
     *    @return a new attribute representing the quota
     */
    Attribute * new_quota(Attribute * va);

private:

    /**
     *  Return the limits for image and size stored in the a given quota.
     *    @param va_ptr the attribute that stores the quota
     *    @param ds the name of the DATASTORE quota
     *    @param images the limit for the number of images
     *    @param size the limit for the total storage size
     *
     *    @return -1 if the limits are wrong 0 otherwise
     */
    int get_limits(Attribute* va_ptr, string& ds, string& images, string& size);

    /**
     *  Return the attribute with the datastore quotas
     *    @param ds_name name of the datastore
     *    @return pointer to the datastore quota or 0 if not found
     */
    VectorAttribute * get_datastore_quota(const string& ds_name);

    /**
     *  Return the attribute with the datastore quotas
     *    @param resource attribute describing a datastore quota
     *    @return pointer to the datastore quota or 0 if not found
     */
    Attribute * get_quota(Attribute * resource);
};

#endif /*QUOTA_DATASTORE_H_*/