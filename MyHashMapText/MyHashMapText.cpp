// MyHashMapText.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

#ifndef _HASHMAP_H_
#define _HASHMAP_H_

//首先要定义hash函数与比较函数
class HashFuncMethod
{
public:
	int operator()(const string & key )
	{
		int hash = 0;
		for(int i = 0; i < key.length(); ++i)
		{
			hash = hash << 7 ^ key[i];
		}
		return (hash & 0x7FFFFFFF);
	}
};

class EqualKeyMethod
{
public:
	bool operator()(const string & A, const string & B)
	{
		if (A.compare(B) == 0)
			return true;
		else
			return false;
	}
};

template<class Key,class Value>
class HashPair
{
public:
	Key _key;
	Value _value;
	HashPair * _next;

	HashPair(Key key,Value value)
	{
		_key = key;
		_value = value;
		_next = NULL;
	};

	~HashPair()
	{

	};

	HashPair & operator = (const HashPair & other)
	{
		_key = other._key;
		_value = other._value;
		_next = other._next;
		return *this;
	};
};

template<class Key,class Value,class HashFun,class KeyEqual>
class MyHashMap
{
public:
	MyHashMap<Key,Value,HashFun,KeyEqual>(unsigned int size)
	{
		hashFun = HashFuncMethod();
		equalFun = EqualKeyMethod();
		_size = size;
		table = new HashPair<Key,Value>*[_size];
		for (unsigned i = 0 ; i < _size;++i)
		{
			table[i] = NULL;
		}
	};

	~MyHashMap<Key,Value,HashFun,KeyEqual>()
	{
		for (unsigned i = 0 ; i < _size; ++i)
		{
			HashPair<Key,Value> * currentNode = table[i];
			while(currentNode)
			{
				HashPair<Key,Value> * temp = currentNode;
				currentNode = temp->_next;
				delete temp;
			}
		}
		delete table;
	}

	void insert(const Key & key,const Value & value)
	{
		int index = hashFun(key)%_size;
		HashPair<Key,Value> * node = new HashPair<Key,Value>(key,value);
		node->_next = table[index];
		table[index] = node;
	};

	Value & find(const Key & key)
	{
		int index = hashFun(key) % _size;
		HashPair<Key,Value> * node = table[index];
		if (node)
		{
			HashPair<Key,Value> * currentNode = node;
			while(currentNode)
			{
				if (equalFun(currentNode->_key,key))
				{
					return currentNode->_value;
				}
				else
				{
					currentNode = currentNode->_next;
				}
			}
		}
		else
		{
			return _valueNull;
		}

		return _valueNull;
	};

	bool del(const Key & key)
	{
		int index = hashFun(key)%_size;
		HashPair<Key,Value> * node = table[index];
		HashPair<Key,Value> * pre = NULL; 
		while(node)
		{
			if (equalFun(node->_key,key))
			{
				if (pre == NULL)
				{
					table[index] = node->_next;
				}
				else
				{
					pre->_next = node->_next;
				}
				delete node;
				return true;
			}
			else
			{
				pre = node;
				node = node->_next;
			}
		}
		return false;
	};

	Value & operator [] (const Key & key)
	{
		return find(key);
	};

private:
	HashFun hashFun;
	KeyEqual equalFun;
	HashPair<string,string>**table;
	unsigned int _size;
	Value _valueNull;
};

#endif

//测试用例
int Testmain()
{
	MyHashMap<string, string, HashFuncMethod, EqualKeyMethod> hashmap(6);
	hashmap.insert("hello", "world");hashmap.insert("why", "dream");hashmap.insert("c++", "good");
	hashmap.insert("welcome", "haha");

	hashmap["why"] = "love";
	hashmap["why2"] = "love2";
	cout << hashmap["why"].c_str() << endl;
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	Testmain();

	system("pause");
	return 0;
}

