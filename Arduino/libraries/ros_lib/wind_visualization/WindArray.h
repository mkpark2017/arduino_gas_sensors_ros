#ifndef _ROS_wind_visualization_WindArray_h
#define _ROS_wind_visualization_WindArray_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "wind_visualization/Wind.h"

namespace wind_visualization
{

  class WindArray : public ros::Msg
  {
    public:
      uint32_t WindArray_length;
      typedef wind_visualization::Wind _WindArray_type;
      _WindArray_type st_WindArray;
      _WindArray_type * WindArray;

    WindArray():
      WindArray_length(0), WindArray(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->WindArray_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->WindArray_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->WindArray_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->WindArray_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->WindArray_length);
      for( uint32_t i = 0; i < WindArray_length; i++){
      offset += this->WindArray[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t WindArray_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      WindArray_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      WindArray_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      WindArray_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->WindArray_length);
      if(WindArray_lengthT > WindArray_length)
        this->WindArray = (wind_visualization::Wind*)realloc(this->WindArray, WindArray_lengthT * sizeof(wind_visualization::Wind));
      WindArray_length = WindArray_lengthT;
      for( uint32_t i = 0; i < WindArray_length; i++){
      offset += this->st_WindArray.deserialize(inbuffer + offset);
        memcpy( &(this->WindArray[i]), &(this->st_WindArray), sizeof(wind_visualization::Wind));
      }
     return offset;
    }

    const char * getType(){ return "wind_visualization/WindArray"; };
    const char * getMD5(){ return "f9231cca380fd434e867ffec9eda8851"; };

  };

}
#endif