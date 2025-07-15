#pragma once

template <typename T>
class IClone
{
public: 

    IClone(const IClone& proj) = delete;
    IClone& operator=(const IClone& clone) = delete;
    IClone(IClone&& clone) = delete;
    IClone& operator=(IClone&& clone) = delete;
  

    virtual T* Clone() const = 0;


private:
    IClone()
    {
    };
    friend T;
};

