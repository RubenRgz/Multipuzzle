/********************************************************************/
/**
* @LC	  2017/10/18
* @file   Module.h
* @Author Rubén Rodríguez Serrano (rubn2113@gmail.com)
* @date   2017/10/16
* @brief  It is a specialized type of singleton.
* Module must be manually started up and shut down
* before and after use.
* @bug	  No known bugs.
*/
/********************************************************************/
#pragma once

/************************************************************************/
/* Includes												                */
/************************************************************************/
#include <functional>

/************************************************************************************************************************/
/**
* @brief	Represents one engine module. Essentially it is a specialized type of singleton. Module must be manually
*			started up and shut down before and after use.
*/
/************************************************************************************************************************/
template <class T, class ...Args>
class Module
{
public:
	/************************************************************************************************************************/
	/**
	* @brief	Returns a reference to the module instance. Module has to have been started up first otherwise an exception
	*			will be thrown.
	*/
	/************************************************************************************************************************/
	static T& Instance()
	{
		if (IsShutDown())
		{
			printf("Module : In Function : Instance() : Trying to access a module but it hasn't been started up yet.\n");
		}

		if (IsDestroyed())
		{
			printf("Module : In Function : Instance() : Trying to access a destroyed module.\n");
		}

		return *_Instance();
	}

	/************************************************************************************************************************/
	/**
	* @brief	Returns a pointer to the module instance. Module has to have been started up first otherwise an exception
	*			will be thrown.
	*/
	/************************************************************************************************************************/
	static T* InstancePtr()
	{
		if (IsShutDown())
		{
			printf("Module : In Function : InstancePtr() : Trying to access a module but it hasn't been started up yet.\n");
			return NULL;
		}

		if (IsDestroyed())
		{
			printf("Module : In Function : InstancePtr() : Trying to access a destroyed module.\n");
			return NULL;
		}

		return _Instance();
	}

	/************************************************************************************************************************/
	/**
	* @brief	Constructs and starts the module using the specified parameters.
	*/
	/************************************************************************************************************************/
	static bool StartUp(Args &&...args)
	{
		if (!IsShutDown())
		{
			printf("Module : In Function : StartUp() : Trying to start an already started module.\n");
			return false;
		}

		_Instance() = new T;
		IsShutDown() = false;

		return _Instance()->__OnStartUp(std::forward<Args>(args)...);
	}

	/************************************************************************************************************************/
	/**
	* @brief	Shuts down this module and frees any resources it is using.
	*/
	/************************************************************************************************************************/
	static void ShutDown()
	{
		if (IsShutDown())
		{
			printf("Module : In Function : ShutDown() : Trying to shut down an already shut down module.\n");
			return;
		}

		((Module*)_Instance())->OnShutDown();

		delete(_Instance());
		IsShutDown() = true;
	}

	/************************************************************************************************************************/
	/**
	* @brief	Query if the module has been started.
	*/
	/************************************************************************************************************************/
	static bool IsStarted()
	{
		return !IsShutDown() && !IsDestroyed();
	}

protected:
	Module()
	{
	}

	virtual ~Module()
	{
		_Instance() = nullptr;
		IsDestroyed() = true;
	}

	Module(const Module&)
	{

	}

	Module& operator=(const Module&)
	{
		return *this;
	}

private:
	std::function<bool(Args...)>__OnStartUp;									/*!< Pointer to init function of class */

protected:
	/************************************************************************************************************************/
	/**
	* @brief	Connection between standard function and class function 
	*
	* @note		This function needs to be called within all inherit constructor classes
	*/
	/************************************************************************************************************************/
	void Connect(std::function<bool(Args...)>func)
	{
		__OnStartUp = func;
	}

	/************************************************************************************************************************/
	/**
	* @brief	Override if you want your module to be notified just before it is deleted.
	*
	* @note		Useful when your module is polymorphic and you might want to perform some kind of clean up perhaps overriding
	*			that of a base class.
	*/
	/************************************************************************************************************************/
	virtual void OnShutDown()
	{

	}

	/************************************************************************************************************************/
	/**
	* @brief	Returns a singleton instance of this module. Throws an exception if module is not yet initialized.
	*/
	/************************************************************************************************************************/
	static T*& _Instance()
	{
		static T* inst = nullptr;
		return inst;
	}

	/************************************************************************************************************************/
	/**
	* @brief	Checks has the Module been shut down.
	*
	* @note		If module was never even started, this will return false.
	*/
	/************************************************************************************************************************/
	static bool& IsDestroyed()
	{
		static bool inst = false;
		return inst;
	}

	/************************************************************************************************************************/
	/**
	* @brief	Checks has the Module been started up.
	*/
	/************************************************************************************************************************/
	static bool& IsShutDown()
	{
		static bool inst = true;
		return inst;
	}
};

