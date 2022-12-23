#include <iostream>
#include "String.h"
using namespace std;

String :: String(const char *s)
{
    head = ListNode::stringToList(s);
}

String :: String(const String & s){
    String::ListNode* s_copy = String::ListNode::copy(s.head);
    head = s_copy;
}

String String :: operator = (const String & s){
    String::ListNode::deleteList(head);
    String::ListNode* s_copy = String::ListNode::copy(s.head);
    head = s_copy;
    return s;
}

char & String :: operator [] (const int index){
    int myIndex = 0;
    ListNode*p = head;
    for ( p; myIndex < index; p = p->next ){
        myIndex++;
    }
    return p->info;
}
 
int String::size() const{
    return String::ListNode::length(head);
}

int String::indexOf( char c) const{
    ListNode*check= String::ListNode::find(c, head);
    int myIndex = 0;
    for ( ListNode * p = head; p != nullptr; p = p->next ){
        if (p->info == check->info){
            return myIndex;
        }
        myIndex++;
    }
    return myIndex;
    }


int String::indexOf( const String & pattern) const{
    if (head == nullptr){
        return 0;
    }
    ListNode * p = head;

    int myIndex = 0;
    while (p != nullptr){
        if (String::ListNode::compare2(p, pattern.head) == 1){
            return myIndex;
        }
        myIndex++;
        p = p->next;
    }

    return 0;
}


bool String:: operator > (const String & s) const{
    if (String::ListNode::compare(head, s.head) > 0){
        return true;
    }
    else
        return false;
}

bool String:: operator >= (const String & s) const{
    if (String::ListNode::compare(head, s.head) >= 0){
        return true;
    }
    else
        return false;
}


bool String:: operator < (const String & s) const{
    if (String::ListNode::compare(head, s.head) < 0){
        return true;
    }
    else
        return false;
}

bool String:: operator <= (const String & s) const{
    if (String::ListNode::compare(head, s.head) <= 0){
        return true;
    }
    else
        return false;
}

bool String:: operator == (const String & s) const{
    if (String::ListNode::compare(head, s.head) == 0){
        return true;
    }
    else
        return false;
}
bool String:: operator != (const String & s) const{
    if (String::ListNode::compare(head, s.head) != 0){
        return true;
    }
    else
        return false;
}

String String:: operator + (const String & s) const{
    String::ListNode* s_copy = String::ListNode::copy(s.head);
    String::ListNode* head_copy = String::ListNode::copy(head);
    String temp;
    String::ListNode* added = String::ListNode::append(head_copy, s_copy);
    String::ListNode::deleteList(head_copy);
    String::ListNode::deleteList(s_copy);
    temp.head = added;
    return temp;
}

String String:: operator += (const String & s){
    String::ListNode* s_copy = String::ListNode::copy(s.head);
    String::ListNode* result = String::ListNode::append(head, s_copy);
    String::ListNode::deleteList(head); // try deleting this maybe
    String::ListNode::deleteList(s_copy);
    head = result;
    return *this;
}

String String::reverse() const{
    String temp;
    String::ListNode* reversedLL = String::ListNode::reverse(head);
    temp.head = reversedLL;
    return temp;
}


String::ListNode* String::ListNode::stringToList(const char*s){
    return !*s ? nullptr : new ListNode(*s, stringToList(s+1));
}

void String::ListNode::deleteList(ListNode * L){
    if ( L != nullptr )
    {
      deleteList( L->next );
      delete L;
    }
}

String::ListNode * String::ListNode::copy(ListNode * L )
 {
    return L == nullptr ? nullptr: new ListNode( L->info, copy( L->next ) );
 }


String::ListNode * String::ListNode::find(char c, ListNode *L){
    return L == nullptr ? nullptr : L->info == c ? L : find( c, L->next );
}

String::ListNode * String::ListNode::append(ListNode * L1, ListNode *L2){
    return L1 == nullptr ? copy( L2 )
      : new ListNode( L1->info, append( L1->next, L2 ) );
}

String::ListNode * String::ListNode::reverse(ListNode * L){
    ListNode * result = nullptr;
    for ( ListNode * p = L; p != nullptr; p = p->next )
      result = new ListNode( p->info, result );
    return result;
}

int String::ListNode::length(ListNode * L){
    return L == 0 ? 0 : 1 + length( L->next );
}


int String::ListNode::compare(ListNode * L1, ListNode * L2){
    while ((L1 != nullptr && L2 != nullptr) && (L1->info == L2->info)){
            L1 = L1->next;
            L2 = L2->next;
        }
        if (L1 == L2)
            return 0;
        if (L1 == nullptr)
            return -1;
        if (L2 == nullptr)
            return 1;
        if (L1->info > L2->info)
            return 1;
        else
            return -1;
    }

int String::ListNode::compare2(ListNode * L1, ListNode * L2){
    while (L2 != nullptr){
        if (L1->info != L2->info){
            return 0;
        }
        L1 = L1->next;
        L2 = L2->next;
        if (L1 == nullptr && L2 == nullptr)
            return 1;
        if (L1 == nullptr && L2 != nullptr)
            return 0;
    }
    return 1;
}

String :: ~String()
{
    ListNode * temp;
    for ( ListNode * p = head; p != nullptr; )
    {
    temp = p;
    p = p->next;
    delete temp; 
    }
}


void String:: print( ostream & out )const{
    for ( ListNode * p = head; p != nullptr; p = p->next )
        out << p->info << ' ';
}

void String::read(istream & in)
{
	char buf[1024];
	in.getline(buf, 1024);
	String::ListNode::deleteList(head);
	head = String::ListNode::stringToList(buf);
}

ostream & operator << (ostream & out, String str){
    str.print(out);
    return out;
}
istream & operator >> (istream & in, String & str){
    str.read(in);
    return in;
}
