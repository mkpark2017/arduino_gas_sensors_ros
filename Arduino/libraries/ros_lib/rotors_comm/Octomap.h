#ifndef _ROS_SERVICE_Octomap_h
#define _ROS_SERVICE_Octomap_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "octomap_msgs/Octomap.h"
#include "geometry_msgs/Point.h"

namespace rotors_comm
{

static const char OCTOMAP[] = "rotors_comm/Octomap";

  class OctomapRequest : public ros::Msg
  {
    public:
      typedef geometry_msgs::Point _bounding_box_origin_type;
      _bounding_box_origin_type bounding_box_origin;
      typedef geometry_msgs::Point _bounding_box_lengths_type;
      _bounding_box_lengths_type bounding_box_lengths;
      typedef float _leaf_size_type;
      _leaf_size_type leaf_size;
      typedef bool _publish_octomap_type;
      _publish_octomap_type publish_octomap;
      typedef const char* _filename_type;
      _filename_type filename;

    OctomapRequest():
      bounding_box_origin(),
      bounding_box_lengths(),
      leaf_size(0),
      publish_octomap(0),
      filename("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->bounding_box_origin.serialize(outbuffer + offset);
      offset += this->bounding_box_lengths.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->leaf_size);
      union {
        bool real;
        uint8_t base;
      } u_publish_octomap;
      u_publish_octomap.real = this->publish_octomap;
      *(outbuffer + offset + 0) = (u_publish_octomap.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->publish_octomap);
      uint32_t length_filename = strlen(this->filename);
      varToArr(outbuffer + offset, length_filename);
      offset += 4;
      memcpy(outbuffer + offset, this->filename, length_filename);
      offset += length_filename;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->bounding_box_origin.deserialize(inbuffer + offset);
      offset += this->bounding_box_lengths.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->leaf_size));
      union {
        bool real;
        uint8_t base;
      } u_publish_octomap;
      u_publish_octomap.base = 0;
      u_publish_octomap.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->publish_octomap = u_publish_octomap.real;
      offset += sizeof(this->publish_octomap);
      uint32_t length_filename;
      arrToVar(length_filename, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_filename; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_filename-1]=0;
      this->filename = (char *)(inbuffer + offset-1);
      offset += length_filename;
     return offset;
    }

    const char * getType(){ return OCTOMAP; };
    const char * getMD5(){ return "75da936d054df9de7938d7041a8a6ef2"; };

  };

  class OctomapResponse : public ros::Msg
  {
    public:
      typedef octomap_msgs::Octomap _map_type;
      _map_type map;
      typedef float _origin_latitude_type;
      _origin_latitude_type origin_latitude;
      typedef float _origin_longitude_type;
      _origin_longitude_type origin_longitude;
      typedef float _origin_altitude_type;
      _origin_altitude_type origin_altitude;

    OctomapResponse():
      map(),
      origin_latitude(0),
      origin_longitude(0),
      origin_altitude(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->map.serialize(outbuffer + offset);
      offset += serializeAvrFloat64(outbuffer + offset, this->origin_latitude);
      offset += serializeAvrFloat64(outbuffer + offset, this->origin_longitude);
      offset += serializeAvrFloat64(outbuffer + offset, this->origin_altitude);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->map.deserialize(inbuffer + offset);
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->origin_latitude));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->origin_longitude));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->origin_altitude));
     return offset;
    }

    const char * getType(){ return OCTOMAP; };
    const char * getMD5(){ return "57e29816a04b311c573d5337632a1156"; };

  };

  class Octomap {
    public:
    typedef OctomapRequest Request;
    typedef OctomapResponse Response;
  };

}
#endif
