#pragma once

#include "common/mixin/not_copyable.h"

#include "runtime/memory_resource/memory_resource.h"

namespace memory_resource {
namespace details {

class memory_ordered_chunk_list;

class memory_chunk_tree : vk::not_copyable {
public:
  class tree_node;

  void hard_reset() noexcept { root_ = nullptr; }
  void insert(void *mem, size_type size) noexcept;
  tree_node *extract(size_type size) noexcept;
  tree_node *extract_smallest() noexcept;

  static size_type get_chunk_size(tree_node *node) noexcept;

  void flush_to(memory_ordered_chunk_list &mem_list) noexcept;

private:
  void flush_node_to(tree_node *node, memory_ordered_chunk_list &mem_list) noexcept;
  tree_node *search(size_type size, bool lower_bound) noexcept;

  void left_rotate(tree_node *node) noexcept;
  void right_rotate(tree_node *node) noexcept;
  void fix_red_red(tree_node *node) noexcept;
  tree_node *find_replacer(tree_node *node) noexcept;
  void detach_leaf(tree_node *detaching_node) noexcept;
  void detach_node_with_one_child(tree_node *detaching_node, tree_node *replacer) noexcept;
  void swap_detaching_node_with_replacer(tree_node *detaching_node, tree_node *replacer) noexcept;
  void detach_node(tree_node *detaching_node) noexcept;
  void fix_double_black(tree_node *node) noexcept;

  tree_node *root_{nullptr};
};

} // namespace details
} // namespace memory_resource
