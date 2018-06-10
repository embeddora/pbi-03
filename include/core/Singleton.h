//
// Copyright (c) 2018 [n/a] info@embeddora.com All rights reserved
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//        * Redistributions of source code must retain the above copyright
//          notice, this list of conditions and the following disclaimer.
//        * Redistributions in binary form must reproduce the above copyright
//          notice, this list of conditions and the following disclaimer in the
//          documentation and/or other materials provided with the distribution.
//        * Neither the name of The Linux Foundation nor
//          the names of its contributors may be used to endorse or promote
//          products derived from this software without specific prior written
//          permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NON-INFRINGEMENT ARE DISCLAIMED.    IN NO EVENT SHALL THE COPYRIGHT OWNER OR
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Abstract:            a definition of locally used 'Singleton'
//
// Usage:               none
//
// Version:             0.0.2

#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "Uncopyable.h"


/**
 * Any class that inherits from Singleton become itself a singleton.
 *
 * \remark
 * Singleton can't be copied and can't be instanciated (new).
 *
 * \author  Constantin M.
 */
template<class T> class Singleton : virtual private Uncopyable<Singleton<T>>
{
private:
	friend T;

private:
	// Can't be instanciated
	Singleton() = default;

	virtual ~Singleton() = default;

public:
        /**
         * Returns the singleton instance.
         *
         * \return Singleton instance.
         */
        static T& getInstance()
	{
		static T m;

		return m;
        }

        /**
         * Returns the pointer to the singleton instance.
         *
         * \return Pointer to the singleton instance.
         */
        static T* getInstancePtr()
	{
		return &Singleton<T>::getSingleton();
        }
};

#endif // #ifndef _SINGLETON_H_
