
#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

typedef std::vector<std::string> TStringVector;
typedef std::pair<std::string, std::string> TStringStringPair;
typedef std::unordered_map<std::string, std::string> TStringStringUnorderedMap;
typedef std::vector<TStringStringUnorderedMap> TStringStringUnorderedMapVector;

struct ConfigurationNode;

typedef ConfigurationNode * PConfigurationNode;
typedef std::unordered_map<std::string, std::unique_ptr<ConfigurationNode>> TStringConfigurationNodeUnorderedMap;

#endif