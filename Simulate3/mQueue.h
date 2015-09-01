/*
*Author	:	bianzhiyu@126.com
*IDE	:	VS2013
*Tiem	:	2015/08/27 , 14:56
*In one namespace : mclstd
*A custom template class mQueue , with standard fist-in-fisrt-out property
*  template <class State>  class mQueue
*	method: int getSize() const ; void pushin(const State& mm) ; void popout()
*			State getHead() const ; State getTail() const
*/
#ifndef __mQueueh
#define __mQueueh

#include <iostream>

/* Tail==&Head means size==0
* Tail->Next==NULL
* when size>0, pt==Tail means the last node
*/
namespace mclstd
{
	template <class State>
	class mQueue
	{
	public:
		template<class State>
		class mNode
		{
		public:
			State Cont;
			mNode<State>* Next;
		public:
			mNode() :Cont()
			{
				Next = NULL;
			}
			mNode(const mNode& mm) :Cont(mm.Cont) { Next = mm.Next; }
			mNode(const State& ss, mNode* pt) :Cont(ss) { Next = pt; }
			mNode& operator = (const mNode& mm)
			{
				Cont = mm.Cont;
				Next = mm.Next;
				return *this;
			}
		};
	protected:
		int Size;
		mNode<State> Head, *Tail;
	public:
		//Constructor
		mQueue() :Head()
		{
			Size = 0;	Tail = &Head;
		}
		int getSize() const { return Size; }
		void pushin(const State& mm)
		{
			mNode<State> * pt = new mNode<State>;
			pt->Cont = mm;
			pt->Next = NULL;
			Tail->Next = pt;
			Tail = pt;
			Size++;
		}//consider : 0 -> 1,  and 1-> 2  ;  malloc memory
		void popout()
		{
			if (Size < 1)	return;
			mNode<State>* pt = &Head;
			while (pt->Next != Tail)
				pt = pt->Next;
			pt->Next = NULL;
			delete Tail;
			Tail = pt;
			Size--;
		}//2->1,  and 1->0 :  ; free memory
		State getHead() const
		{
			if (Size > 0)	return (Head.Next->Cont);
			else return Head.Cont;
		}
		State getTail() const
		{
			return Tail->Cont;
		}
		//copy Constructor
		mQueue(const mQueue& mm)
		{
			Size = mm.Size;
			Head = mm.Head;

			if (mm.getSize() == 0)
			{
				Tail = NULL;
				return;
			}

			mNode<State> *mpt = mm.Head.Next, *pt = new mNode<State>;
			pt->Cont = mpt->Cont;
			pt->Next = NULL;
			Head.Next = pt;

			while (mpt->Next)
			{
				mpt = mpt->Next;
				mNode<State> *tmp = new mNode<State>(mpt->Cont, NULL);
				pt->Next = tmp;
				pt = pt->Next;
			}
			Tail = pt;
		}	//malloc memory
		//operator=
		mQueue& operator = (const mQueue& mm)
			// free *this; re malloc memory
		{
			this->~mQueue();

			Size = mm.Size;
			Head = mm.Head;

			if (mm.getSize() == 0)
			{
				Tail = NULL;
				return *this;
			}

			mNode<State> * pt = new mNode<State>(mm.Head.Next->Cont, NULL), *mpt = mm.Head.Next;
			Head.Next = pt;

			while (mpt->Next)
			{
				mpt = mpt->Next;
				mNode<State> *tmp = new mNode<State>(mpt->Cont, NULL);
				pt->Next = tmp;
				pt = pt->Next;
			}
			Tail = pt;

			return *this;
		}
		void disposeAll()
		{
			if (Size < 1) return;

			mNode<State> * pt = Head.Next, *pt2;
			while (pt)
			{
				pt2 = pt->Next;
				delete pt;
				pt = pt2;
			}

			Size = 0;
			Head.Next = 0;
			Tail = &(Head);
		}
		~mQueue()
		{
			if (Size < 1) return;

			mNode<State> * pt = Head.Next, *pt2;
			while (pt)
			{
				pt2 = pt->Next;
				delete pt;
				pt = pt2;
			}

			Size = 0;
			Head.Next = 0;
			Tail = &(Head);
		}

	public:
		void show(std::ostream& osm = std::cout) const
		{
			if (Size < 1) return;
			mNode<State> * pt = Head.Next;
			while (pt)
			{
				std::cout << pt->Cont << "\t";
				pt = pt->Next;
			}
		}

		template<class State>
		friend std::ostream& operator << (std::ostream & osm, const mQueue<State>& mm);

		mQueue<State>& append(const State& mm)
		{
			this->pushin(mm);
			return *this;
		}
	};

	template<class State>
	std::ostream& operator << (std::ostream & osm, const mQueue<State>& mm)
	{
		if (mm.Size < 1) return osm;
		mNode<State> *pt = mm.Head.Next;
		while (pt)
		{
			osm << pt->Cont << "\t";
			pt = pt->Next;
		}
		return osm;
	}
}
#endif