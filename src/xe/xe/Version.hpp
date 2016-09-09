/**
 * @file 
 * @brief 
 */


/*
 * Copyright (c) 2013 Felipe Apablaza.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution.
 */

#ifndef __EXENG_VERSION_HPP__
#define __EXENG_VERSION_HPP__

#include <xe/PreDef.hpp>
#include <iostream>

namespace xe {
    /**
     * @brief Permite representar versiones de los diferentes componentes
     */
    class XE_API Version {
    public:
        Version();
        Version(int Major, int Minor, int Revision, int Build);
        Version(const Version& Other);
        
        void setup(int Major, int Minor, int Revision, int Build);
        
        int getMajor() const;
        int getMinor() const;
        int getRevision() const;
        int getBuild() const;
        
        void setMajor(int Value);
        void setMinor(int Value);
        void setRevision(int Value);
        void setBuild(int Value);
        
        bool operator!= (const Version &Other) const;
        bool operator== (const Version &Other) const;
        
        bool operator>= (const Version &Other) const;
        bool operator<= (const Version &Other) const;
        
        bool operator>     (const Version &Other) const;
        bool operator<     (const Version &Other) const;

        inline friend std::ostream& operator<< (std::ostream &os, const Version& version) {
            os    << version.getMajor();
            os    << "." << version.getMinor();
            os    << "." << version.getRevision();
            os    << "." << version.getBuild();
                
            return os;
        }

    private:
        int _major = 0;
        int _minor = 0;
        int revision = 0;
        int build = 0;
    };
    
    inline Version::Version() {}
    
    inline Version::Version(int Major, int Minor, int Revision, int Build) {
        this->setup(Major, Minor, Revision, Build);
    }
    
    inline Version::Version(const Version& Other) {
        *this = Other;
    }
    
    inline int Version::getMajor() const {
        return this->_major;
    }
    
    inline int Version::getMinor() const {
        return this->_minor;
    }
    
    inline int Version::getRevision() const {
        return this->revision;
    }
    
    inline int Version::getBuild() const {
        return this->build;
    }
    
    inline void Version::setMajor(int Value) {
        this->_major = Value;
    }
    
    inline void Version::setMinor(int Value) {
        this->_minor = Value;
    }
        
    inline void Version::setRevision(int Value) {
        this->revision = Value;
    }
    
    inline void Version::setBuild(int Value) {
        this->build = Value;
    }
}

#endif    //__EXENG_VERSION_HPP__
