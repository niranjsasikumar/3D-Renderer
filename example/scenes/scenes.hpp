#ifndef SCENES_H
#define SCENES_H
#include <string>
#include <map>
#include "scene1.hpp"
#include "scene2.hpp"
#include "scene3.hpp"

Scene getScene(const std::string& name) {
  std::map<std::string, Scene> scenes;
  scenes.insert(std::pair<std::string, Scene>("scene1", getScene1()));
  scenes.insert(std::pair<std::string, Scene>("scene2", getScene2()));
  scenes.insert(std::pair<std::string, Scene>("scene3", getScene3()));

  return scenes.find(name)->second;
}

#endif