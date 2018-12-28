//
//  TreeStruct.h
//  KnowledgeTree
//
//  Created by Torben Brams on 27/12/2018.
//
#ifndef TREESTRUCT_H
#define TREESTRUCT_H

#include <string>

class TreeStruct {
private:
      typedef struct node {
         std::string object;
         std::string question;
         node* yes;
         node* no;
      }* nodePtr;

      nodePtr head;
      std::string leadinText;
      std::string objectType;
      std::string firstObject;

public:
      TreeStruct();
      ~TreeStruct();
      
      nodePtr newObject(std::string); 
      nodePtr newQuestion(std::string);
      nodePtr extendTree(nodePtr);
      void dumpNode(nodePtr);
      bool ask(std::string);
      void deduct();
};

#endif /* TREESTRUCT_H*/