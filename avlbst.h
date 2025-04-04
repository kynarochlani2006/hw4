#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    void insertFix (AVLNode<Key, Value>* parent, AVLNode<Key, Value>* newOne);
    void doZigZig(AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key, Value>* newOne);
    void doZigZag(AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key, Value>* newOne);
    void rotateRight(AVLNode<Key, Value>* n);
    void rotateLeft(AVLNode<Key, Value>* n);
    void removeFix(AVLNode<Key, Value>* n, int diff);
    AVLNode<Key, Value>* AVLinternalFind(const Key& key) const;

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
  // TODO

  
  if(this->root_ == nullptr){

    AVLNode<Key, Value>* newOne = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
    this->root_ = newOne;
    newOne->setLeft(nullptr);
    newOne->setRight(nullptr);
    newOne->setBalance(0);
    return;
  } else {

    AVLNode<Key, Value>* current = AVLinternalFind(new_item.first);
    if(current != nullptr){
      AVLNode<Key, Value>* c = static_cast<AVLNode<Key, Value>*>(this->root_);
      AVLNode<Key, Value>* parent = nullptr;
      while(c != nullptr){
        parent = c;
        if(new_item.first > c->getKey()){

          if(c->getRight() != nullptr){
            c = c->getRight();
          } else {
            AVLNode<Key, Value>* newInsertNode = new AVLNode<Key, Value>(new_item.first, new_item.second, c);
            c->setRight(newInsertNode);
            if(c->getBalance() == -1){
              c->setBalance(0);
              return;
            } else if(c->getBalance() == 1){
              c->setBalance(0);
              return;
            } else if(c->getBalance() == 0){
              c->setBalance(1);
              insertFix(c, newInsertNode);
              return;
            }
          }

        } else if(new_item.first < c->getKey()){
            
            if(c->getLeft() != nullptr){
              c = c->getLeft();
          } else {
            AVLNode<Key, Value>* newInsertNode = new AVLNode<Key, Value>(new_item.first, new_item.second, c);
            c->setLeft(newInsertNode);
            if(c->getBalance() == -1){
              c->setBalance(0);
              return;
            } else if(c->getBalance() == 1){
              c->setBalance(0);
              return;
            } else if(c->getBalance() == 0){
              c->setBalance(-1);
              insertFix(c, newInsertNode);
              return;
            }
        } else {
            c->setValue(new_item.second);
            return;
        }
      }
    } else {
      current->setValue(new_item.second);
      return;
    }


  }
}
}
*/

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
  if(this->root_ == nullptr){

    AVLNode<Key, Value>* newOne = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
    this->root_ = newOne;
    newOne->setLeft(nullptr);
    newOne->setRight(nullptr);
    newOne->setBalance(0);
    return;
  } else {
    AVLNode<Key, Value>* current = AVLinternalFind(new_item.first);
    if(current == nullptr){
      AVLNode<Key, Value>* c = static_cast<AVLNode<Key, Value>*>(this->root_);
      AVLNode<Key, Value>* parent = nullptr;
      while(c != nullptr){
        parent = c;
        if(new_item.first > c->getKey()){
          if(c->getRight() != nullptr){
            c = c->getRight();
          } else {
            AVLNode<Key, Value>* newInsertNode = new AVLNode<Key, Value>(new_item.first, new_item.second, c);
            c->setRight(newInsertNode);
            newInsertNode->setBalance(0);
            if(c->getBalance() == -1){
              c->setBalance(0);
              
              return;
            } else if(c->getBalance() == 1){
              c->setBalance(0);

              return;
            } else if(c->getBalance() == 0){
              c->setBalance(1);
              insertFix(c, newInsertNode);

              return;
            }
            return;
          }
        } else if(new_item.first < c->getKey()){
          
          if(c->getLeft() != nullptr){
            c = c->getLeft();
          } else {
            AVLNode<Key, Value>* newInsertNode = new AVLNode<Key, Value>(new_item.first, new_item.second, c);
            c->setLeft(newInsertNode);
            newInsertNode->setBalance(0);
            if(c->getBalance() == -1){
              c->setBalance(0);

              return;
            } else if(c->getBalance() == 1){
              c->setBalance(0);

              return;
            } else if(c->getBalance() == 0){
              c->setBalance(-1);
              insertFix(c, newInsertNode);

              return;
            }
            return;
        }
      } else {
        c->setValue(new_item.second);
        return;
      }

    }
  }
  }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix (AVLNode<Key, Value>* parent, AVLNode<Key, Value>* newOne){
    if(parent == nullptr){
        return;
    }
    if(newOne == nullptr){
        return;
    }

    AVLNode<Key, Value>* g = parent->getParent();

    if(g == nullptr){
        return;
    }

    if(g->getLeft() == parent){
      g->updateBalance(-1);
      if(g->getBalance() == 0){
        return;
      }
      if(g->getBalance() == -1){
        insertFix(g, parent);
      } 
      if(g->getBalance() == -2){
        
        if(parent->getBalance() < 0){
          doZigZig(g, parent, newOne);
        } else if(parent->getBalance() > 0){
          
          doZigZag(g, parent, newOne);
        }
      }
    } else {
      g->updateBalance(1);
      
      if(g->getBalance() == 0){
        return;
      }
      if(g->getBalance() == 1){
        insertFix(g, parent);
      } 
      if(g->getBalance() == 2){
        
        if(parent->getBalance() > 0){
          
          doZigZig(g, parent, newOne);
        } else if(parent->getBalance() < 0){
          
          doZigZag(g, parent, newOne);
        }
      }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::doZigZig(AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key, Value>* newOne){
    if(p->getBalance() < 0){
        rotateRight(g);
        p->setBalance(0);
        g->setBalance(0);
    } else if(p->getBalance() > 0){
        
        rotateLeft(g);
        p->setBalance(0);
        g->setBalance(0);
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::doZigZag(AVLNode<Key, Value>* g, AVLNode<Key, Value>* p, AVLNode<Key, Value>* newOne){
    if(p->getBalance() > 0){
        rotateLeft(p);
        rotateRight(g);

        if(newOne->getBalance() == -1){
            p->setBalance(0);
            g->setBalance(1);
            newOne->setBalance(0);
        } else if(newOne->getBalance() == 0){
            p->setBalance(0);
            g->setBalance(0);
            newOne->setBalance(0);
        } else if(newOne->getBalance() == 1){
            p->setBalance(-1);
            g->setBalance(0);
            newOne->setBalance(0);
        }
    } else if(p->getBalance() < 0){
        rotateRight(p);
        rotateLeft(g);

        if(newOne->getBalance() == -1){
            p->setBalance(1);
            g->setBalance(0);
            newOne->setBalance(0);
        } else if(newOne->getBalance() == 0){
            p->setBalance(0);
            g->setBalance(0);
            newOne->setBalance(0);
        } else if(newOne->getBalance() == 1){
            p->setBalance(0);
            g->setBalance(-1);
            newOne->setBalance(0);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value>* n){

  if(!n){
    return;
  } 

  if(n->getLeft() == nullptr){
    return;
  }

    AVLNode<Key, Value>* newerOne = n->getLeft();
    AVLNode<Key, Value>* temp = newerOne->getRight();
    AVLNode<Key, Value>* nParent = n->getParent();

    if(nParent == nullptr){
        this->root_ = newerOne;
        newerOne->setParent(nullptr);

    } else if(n == nParent->getLeft()){
        nParent->setLeft(newerOne);
        newerOne->setParent(nParent);

    } else {
        nParent->setRight(newerOne);
        newerOne->setParent(nParent);
    }

    newerOne->setRight(n);
    n->setLeft(temp);


    if(temp != nullptr){
        temp->setParent(n);
    }

    n->setParent(newerOne);

    //n->updateBalance(0);
    //newerOne->updateBalance(0);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value>* n){

  if(!n){
    return;
  } 

  if(n->getRight() == nullptr){
    return;
  }

    AVLNode<Key, Value>* newerOne = n->getRight();
    AVLNode<Key, Value>* temp = newerOne->getLeft();
    AVLNode<Key, Value>* nParent = n->getParent();

    if(nParent == nullptr){
        this->root_ = newerOne;
        newerOne->setParent(nullptr);
    } else if(n == nParent->getLeft()){
        nParent->setLeft(newerOne);
        newerOne->setParent(nParent);

    } else {
        nParent->setRight(newerOne);
        newerOne->setParent(nParent);
        
    }

    n->setParent(newerOne);
    newerOne->setLeft(n);
    n->setRight(temp);

    if(temp != nullptr){
        temp->setParent(n);
    } 

}


/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO

    AVLNode<Key, Value>* n = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    
    if(n == nullptr){
        return;
    }

    if(n->getLeft() && n->getRight()){
        AVLNode<Key, Value>* pre = static_cast<AVLNode<Key, Value>*>(this->predecessor(n));
        nodeSwap(n, pre);
    }

    AVLNode<Key, Value>* parent = n->getParent();
    AVLNode<Key, Value>* child = nullptr;

    if(n->getLeft() != nullptr){
        child = n->getLeft();
    } else if(n->getRight() != nullptr){
        child = n->getRight();
    }

    int diff = 0;
    if(child != nullptr){
        child->setParent(parent);
    }

    if(parent == nullptr){
        this->root_ = child;
    } else if(parent->getLeft() == n){
        parent->setLeft(child);
        diff = 1;
    } else {
        parent->setRight(child);
        diff = -1;
    }

    delete n;

    removeFix(parent, diff);
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n, int diff){
    if(n == nullptr){
        return;
    }

    AVLNode<Key, Value>* parent = n->getParent();
    int ndiff = 0;
    
    if(parent != nullptr){
        if(parent->getLeft() == n){
            ndiff = 1;
        } else {
            ndiff = -1;
        }
    }

    if(diff == -1){
      if(n->getBalance() + diff == -2){
        AVLNode<Key, Value>* c = n->getLeft();

        if(c->getBalance() == -1){
            rotateRight(n);
            n->setBalance(0);
            c->setBalance(0);
            removeFix(parent, ndiff);
        } else if(c->getBalance() == 0){
            rotateRight(n);
            n->setBalance(-1);
            c->setBalance(1);
            return;
        } else if(c->getBalance() == 1){
            AVLNode<Key, Value>* g = c->getRight();
            rotateLeft(c);
            rotateRight(n);

            if(g->getBalance() == 1){
                n->setBalance(0);
                c->setBalance(-1);
                g->setBalance(0);
            } else if(g->getBalance() == 0){
                n->setBalance(0);
                c->setBalance(0);
                g->setBalance(0);
            } else {
                n->setBalance(1);
                c->setBalance(0);
                g->setBalance(0);
            }
            removeFix(parent, ndiff);
        }
        } else if(n->getBalance() + diff == -1){
            n->setBalance(-1);
            return;
        } else if(n->getBalance() + diff == 0){
            n->setBalance(0);
            removeFix(parent, ndiff);
        }
      } else {
        if(n->getBalance() + diff == 2){
            AVLNode<Key, Value>* c = n->getRight();

            if(c->getBalance() == 1){
                rotateLeft(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(parent, ndiff);
            } else if(c->getBalance() == 0){
                rotateLeft(n);
                n->setBalance(1);
                c->setBalance(-1);
                return;
            } else if(c->getBalance() == -1){
                AVLNode<Key, Value>* g = c->getLeft();
                rotateRight(c);
                rotateLeft(n);

                if(g->getBalance() == -1){
                    n->setBalance(0);
                    c->setBalance(1);
                    g->setBalance(0);
                } else if(g->getBalance() == 0){
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                } else {
                    n->setBalance(-1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                removeFix(parent, ndiff);
            }
        } else if(n->getBalance() + diff == 1){
          n->setBalance(1);
          return;
        } else {
          n->setBalance(0);
          removeFix(parent, ndiff);
        }
      }
    } 
    
template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

template<typename Key, typename Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::AVLinternalFind(const Key& key) const
{
  // TODO

  AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(this->root_);

  while(curr != nullptr){
    if(key == curr->getKey()){
      return curr;
    }

    if(key < curr->getKey()){
      curr = curr->getLeft();
    } else if(key > curr->getKey()){
      curr = curr->getRight();
    }
  }
  return nullptr;
  
}


#endif
