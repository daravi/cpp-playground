#pragma once

#include <algorithm>
#include <array>
#include <exception>
#include <iostream>
#include <filesystem>
#include <functional>
#include <queue>
#include <memory>
#include <mutex>
#include <numeric>
#include <optional>
#include <string>
#include <string_view>
#include <sstream>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/algorithm/string/split.hpp>
#include <fmt/core.h>
#include <spdlog/spdlog.h>

using namespace std;
using vec = std::vector<int>;
using mat = std::vector<std::vector<int>>;

std::vector<std::string> split(const std::string& input, const std::string& delimiter) {
	std::vector<std::string> result;
	boost::split(result, input, boost::is_any_of(delimiter), boost::token_compress_on);
	return result;
}

std::string join(const std::vector<std::string>& input, const std::string& delimiter) {
	return boost::algorithm::join(input, delimiter);
}

/* check if type is specialized from the given template type */
/*************************************************************/
template< class T, template<class...> class Primary >
struct is_specialization_of: std::false_type {};

template< template<class...> class Primary, class... Args >
struct is_specialization_of< Primary<Args...>, Primary> : std::true_type {};

template< class T, template<class...> class Primary >
inline constexpr bool is_specialization_of_v = is_specialization_of<T, Primary>::value;
/*************************************************************/



/* check if type is a container type with size and an iterator */
/***************************************************************/
template< class T, class _ = void >
	struct is_container : std::false_type {};

template< class T >
struct is_container<
	T,
	std::void_t<
		typename T::value_type,
		typename T::size_type,
		typename T::allocator_type,
		typename T::iterator,
		decltype(std::declval<T>().size()),
		decltype(std::declval<T>().begin()),
		decltype(std::declval<T>().end())>
	> : public std::true_type {};
	
template< class T, class _ = void >
inline constexpr bool is_container_v= is_container<T>::value;
/***************************************************************/

// template<typename T, std::enable_if_t<!is_specialization_of_v<T, std::vector>, bool>>
std::ostream& operator<< (std::ostream& out, const std::vector<int>& vec) {
	if (vec.empty()) {
		out << "[]";
		return out;
	}
    
	std::stringstream ss;
	ss << "[";
	for (const auto& e : vec) {
		ss << e << ",";
	}
	ss.seekp(-1, ss.cur);
	ss << "]";

	out << ss.str();
    return out;
}

std::ostream& operator<< (std::ostream& out, const std::vector<char>& vec) {
	if (vec.empty()) {
		out << "[]";
		return out;
	}
    
	std::stringstream ss;
	ss << "[";
	for (const auto& e : vec) {
		ss << e << ",";
	}
	ss.seekp(-1, ss.cur);
	ss << "]";

	out << ss.str();
    return out;
}

// template<typename T, std::enable_if_t<!is_specialization_of_v<T, std::vector>, bool>>
std::ostream& operator<< (std::ostream& out, const std::vector<std::vector<int>>& mat) {
	for (const auto& row : mat) {
		out << row << std::endl;
	}
	return out;
}

std::ostream& operator<< (std::ostream& out, const std::map<char, int>& map) {
	std::stringstream ss;
	ss << "{ ";
	for (auto [c, num] : map) {
		ss << "{" << c << "," << num << "}, ";
	}
	ss.seekp(-2, ss.cur);
	ss << " }";
	out << ss.str();
	return out;
}

std::ostream& operator<< (std::ostream& out, const std::unordered_map<char, int>& map) {
	std::stringstream ss;
	ss << "{ ";
	for (auto [c, num] : map) {
		ss << "{" << c << "," << num << "}, ";
	}
	ss.seekp(-2, ss.cur);
	ss << " }";
	out << ss.str();
	return out;
}

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
	~TreeNode() { delete left; delete right; }
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
    TreeNode(const std::vector<std::optional<int>>& nodes) : TreeNode() {
        if (nodes.empty() or !nodes.at(0)) return;

        val = nodes.at(0).value();

        if (nodes.size() == 1) return;
        
        std::vector<std::optional<int>> leftNodes;
        std::vector<std::optional<int>> rightNodes;
        int n = 1;
        int m = 1;
        for (int i = 1; i < nodes.size(); ++i) {
            if (i < n + m) {
                leftNodes.push_back(nodes.at(i));
            } else if (i < n + (2 * m)) {
                rightNodes.push_back(nodes.at(i));
            }
            
            if (i == (n + (2 * m) - 1)) {
                m = m * 2;
                n = n + m;
            }
        }

        left = new TreeNode(leftNodes);
        right = new TreeNode(rightNodes);
    }
};

std::ostream& operator<< (std::ostream& out, const TreeNode* root) {
	if (root == nullptr) {
		out << "[]";
		return out;
	}
    
	std::stringstream ss;
    ss << "[";
    std::queue<const TreeNode*> nodes;
    nodes.push(root);
    while (!nodes.empty()) {
        auto node = nodes.front();
        nodes.pop();
        if (node) {
            ss << node->val << ", ";
            nodes.push(node->left);
            nodes.push(node->right);
        }
    }
    ss.seekp(-2, ss.cur);
    ss << "]";
    out << ss.str();
    return out;
}

std::ostream& operator<< (std::ostream& out, TreeNode root) {
    return operator<< (out, &root);
}