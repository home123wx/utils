#ifndef _WEAK_TAG_POINTER_H_
#define _WEAK_TAG_POINTER_H_

#include <stdio.h>
#include <assert.h>

template<typename T> class WeakPointer;

template<typename T>
class WeakTagPointer {
private:
    /**
     * @desc 标签 1. 被标识类继承标签指针
     *            2. 当被标识类构建对象时，标签指针中引用计数默认为1
     *            3. 只有当被标识对象释放，标签中的pinter指针会被置为NULL
     *            4. 当标签的引用计数为0时，会释放标签自身
     */
    struct WeakTag {
        WeakTag(T* p): pointer(p), count(1) { }

        /**
         * @desc 减少引用计数，没有被引用释放自身
         */
        void WeakRelease()
        {
            --count;
            if (count <= 0) {
                delete this;
            }
        }

        /**
         * @desc 增加引用计数
         */
        void WeakAddRef() { ++count; }

        /**
         * @desc 获取标签指针
         */
        T* Pointer() const { return pointer; }

        /**
         * @desc 设置标签指针
         */
        void SetPointer(T* pObj) { pointer = pObj; }

    private:
        T* pointer; //标签指针
        int count;  //引用计数
    };

public:
    WeakTagPointer() : m_pWeakTag(NULL) {}

    /**
     * @desc 当子类(及被标识对象)析构时, 触发父类析构。
     *       1. 被标识对象释放，pointer标识被值NULL
     *       2. 通知其他使用者，该指针已无效
     */
    virtual ~WeakTagPointer()
    {
        if (m_pWeakTag != NULL) {
            m_pWeakTag->SetPointer(NULL);
            m_pWeakTag->WeakRelease();
        }
    }

public:
    /**
     * @desc 获取标签指针
     *       1. 指针未空时创建并返回, this指针为被标识对象
     *       2. 每次调用该函数，引用计数加1
     */
    WeakTag* TagPointer()
    {
        if (m_pWeakTag == NULL) {
            m_pWeakTag = new WeakTag(static_cast<T*>(this));
        }

        if (m_pWeakTag != NULL) {
            m_pWeakTag->WeakAddRef();
        }
        return m_pWeakTag;
    }

private:
    template<typename T2> friend class WeakPointer;
    WeakTag* m_pWeakTag;
};

//////////////////////////////////////////////////////////////////////////

/**
 * WeakPointer类，模拟指针的各种操作
 */
template<typename T>
class WeakPointer {
    //typedef typename T::WeakTag WeakTagType;
    struct WeakTagType : public T::WeakTag {};

public:
    WeakPointer():m_pTag(NULL) {}
    ~WeakPointer()
    {
        Release();
    }

public:
    /**
     * @desc 获取标签指针
     */
    T* operator->()
    {
        return GetPointer();
    }

    /**
     * @desc 获取指针对应的引用数据
     */
    T& operator*()
    {
        T* p = GetPointer();
        assert(p != NULL);
        return *p;
    }

    /**
     * @desc bool重载
     */
    operator bool()
    {
        return IsValid();
    }

    //////////////////////////////////////////////////////////////////////////
    //等于
    //////////////////////////////////////////////////////////////////////////
    /**
     * @desc 对指定类型指针赋值
     */
    void operator=(T* pObj)
    {
        WeakTagType* pTag = NULL;
        if (pObj != NULL) {
            //获取对象中标识
            WeakTagType* pTag = static_cast<WeakTagType*>(pObj->TagPointer());
            if (pTag != NULL) {
                //释放自身标识数据
                Release();
            }
        }
        //赋值
        m_pTag = pTag;
    }

    /**
     * @desc 同类型pointer的赋值
     * @param [in] pObj 同类型弱指针
     */
    WeakPointer& operator=(WeakPointer& obj)
    {
        if (this != &obj) {
            operator=(obj.GetPointer());
        }
        return *this;
    }

    /**
     * @desc 不同类型pointer的赋值
     * @param [in] pObj 其他类型弱指针
     */
    template<typename T2>
    void operator=(WeakPointer<T2>& obj)
    {
        operator=(obj.GetPointer());
    }

    //////////////////////////////////////////////////////////////////////////
    //等于等于
    //////////////////////////////////////////////////////////////////////////

    /**
     * @desc 判断同类型弱指针是否相同
     */
    bool operator==(WeakPointer& obj)
    {
        return IsEqual(obj);
    }

    /**
     * @desc 判断和表示类型的指针是否相同
     */
    bool operator==(T* pObj)
    {
        return IsEqual(pObj);
    }

    /**
     * @desc 判断和表示类型的指针是否相同, 特例NULL
     */
    bool operator==(const int&)
    {
        return !IsValid();
    }

    /**
     * @desc 判断和其他类型的弱指针是否不同
     */
    template<typename T2>
    bool operator==(WeakPointer<T2>& obj)
    {
        return IsEqual(obj);
    }

    //////////////////////////////////////////////////////////////////////////
    //不等于
    //////////////////////////////////////////////////////////////////////////
    /**
     * @desc 判断同类型弱指针是否不同
     */
    bool operator!=(WeakPointer& obj)
    {
        return !IsEqual(obj);
    }

    /**
     * @desc 判断和指针是否不同, 特例NULL
     */
    bool operator!=(const int&)
    {
        return IsValid();
    }

    /**
     * @desc 判断和表示类型的指针是否不同
     */
    bool operator!=(T* pObj)
    {
        return !IsEqual(pObj);
    }

    //////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////
    /**
     * @desc 获取标签指针
     */
    T* GetPointer()
    {
        T* p = NULL;
        if (m_pTag != NULL) {
            p = static_cast<T*>(m_pTag->Pointer());
        }
        return p;
    }

    /**
     * @desc 判断标签的有效性
     * @return 是否有效
     */
    bool IsValid() const
    {
        return (m_pTag != NULL) && (m_pTag->Pointer() != NULL);
    }

private:
    WeakPointer(const WeakPointer&);

    /**
     * @desc 判断两个同类型弱指针是否相同
     */
    bool IsEqual(WeakPointer& obj)
    {
        return IsEqual(obj.m_pTag, obj.GetPointer());
    }

    /**
     * @desc 判断两个弱指针是否相同
     */
    template<typename T2>
    bool IsEqual(WeakPointer<T2>& obj)
    {
        return false;
    }

    bool IsEqual(WeakTagType* pTag, T* pObj)
    {
        bool b = false;
        if (m_pTag == NULL && pTag == NULL) {
            b = true;
        } else if (m_pTag != NULL && pTag != NULL) {
            bool b0 = (m_pTag == pTag);
            bool b1 = (m_pTag->Pointer() == pObj);
            b = (b0 && b1);
        }
        return b;
    }

    //
    bool IsEqual(T* pObj)
    {
        bool b = false;
        if (m_pTag != NULL && pObj != NULL) {
            b = (m_pTag->Pointer() == pObj);
        }
        return b;
    }

    /**
     * 释放标签数据
     */
    void Release()
    {
        if (m_pTag != NULL) {
            m_pTag->WeakRelease();
        }
    }

private:
    template<typename T2> friend class WeakPointer;
    WeakTagType* m_pTag;
};

#endif //_WEAK_TAG_POINTER_H_
