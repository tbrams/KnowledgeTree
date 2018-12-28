//
//  TreeStruct.cpp
//  KnowledgeTree
//
//  Created by Torben Brams on 27/12/2018.
//
#include "TreeStruct.h"
#include <cstdlib>
#include <iostream>
#include <string>

TreeStruct::TreeStruct() {
  leadinText = "Are you visualising";
  objectType = "an animal";
  firstObject = "a pigeon";

  head = newQuestion("\n\n"+leadinText + " " + objectType);
  head->yes = newObject(firstObject);
}

TreeStruct::~TreeStruct() {}

TreeStruct::nodePtr TreeStruct::newObject(std::string obj) {
  nodePtr newObj = new node;
  newObj->object = obj;
  newObj->question = "";
  newObj->yes = NULL;
  newObj->no = NULL;

  return newObj;
}

TreeStruct::nodePtr TreeStruct::newQuestion(std::string question) {
  nodePtr newObj = new node;
  newObj->object = "";
  newObj->question = question;
  newObj->yes = NULL;
  newObj->no = NULL;

  return newObj;
}

TreeStruct::nodePtr TreeStruct::extendTree(nodePtr cPtr) {
  std::string question;
  std::string reply;
  std::string object;

  std::cout << "What is it then ?";
  getline(std::cin, object);

  std::cout << "What do I need to ask in order to tell\nthe difference between "
            << cPtr->object << " and " << object << "? ";
  getline(std::cin, question);

  // remove questionmarks (added automatically later)
  for (auto &c : question) if (c=='?') c=' ';


  nodePtr newQuestionPtr = TreeStruct::newQuestion(question);

  std::string tempAnswer = "And what is the answer for " + object + "? ";
  if (ask(tempAnswer)) {
    newQuestionPtr->yes = newObject(object);
    newQuestionPtr->no = cPtr;
  } else {
    newQuestionPtr->no = newObject(object);
    newQuestionPtr->yes = cPtr;
  }

  return newQuestionPtr;
}

bool TreeStruct::ask(std::string question) {
  std::string reply;
  std::cout << question;
  getline(std::cin, reply);

  // Convert reply to uppercase
  for (auto &c : reply) c = toupper(c);

  if (reply[0] == 'Y')
    return true;
  else
    return false;
}

void TreeStruct::deduct() {
  bool enough = false;
  nodePtr current = head;
  nodePtr parent = NULL;

  std::string reply = "";

  do {
    std::string currentQuestion = current->question;
    if (currentQuestion != "") {
      if (ask(current->question + "? ")) {
        if (current->yes != NULL) {
        // move pointer forward in the yes direction
        parent = current;
        current = current->yes;
        } else {
          std::cout << "Unexpected error - no content in node" << std::endl;
          enough=true;
        }
      } else {
        if (current->no != NULL) {
          // move pointer forward in the no direction
          parent = current;
          current = current->no;
        } else {
          // Exit here
          std::cout << "OK, thanks for spending time at this..." << std::endl;
          enough = true;
        }
      }
    } else {
      // We have reached an end node - check if we know the answer
      if (ask("Is it " + current->object + "? ")) {
        // We did ... terminate this round
        std::cout << "Yeah...I knew it!"<<std::endl;
        current=head;
      } else {
        // We need to extend our knowledge tree
        if (parent == head)
          parent->yes = extendTree(current);
        else
          parent->no = extendTree(current);
        current = head;
      }
    }
  } while (!enough);
};