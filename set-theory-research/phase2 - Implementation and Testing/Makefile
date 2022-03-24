# Copyright 2021 Teodora Stroe
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra

HASHMAP_DIR=hashmap
HASHMAP=$(HASHMAP_DIR)/Hashtable.c
LINKEDLIST=$(HASHMAP_DIR)/LinkedList.c

TREAP=treap/treap.c

AVL=avl/avl.c

TEST_HT_DIR=test_ht
TEST_TREAP_DIR=test_treap
TEST_AVL_DIR=test_avl

SOURCES_HT := $(shell find $(TEST_HT_DIR) -name '*.c')
SOURCES_TREAP := $(shell find $(TEST_TREAP_DIR) -name '*.c')
SOURCES_AVL := $(shell find $(TEST_AVL_DIR) -name '*.c')

TARGETS=exec_ht exec_treap exec_avl

build: $(TARGETS)

run-p1: build
	./exec_ht

run-p2: build
	./exec_treap

run-p3: build
	./exec_avl

run-best: run-p3

exec_ht: $(SOURCES_HT) $(HASHMAP) $(LINKEDLIST)
	$(CC) $^ -o $@

exec_treap: $(SOURCES_TREAP) $(TREAP)
	$(CC) $^ -o $@

exec_avl: $(SOURCES_AVL) $(AVL)
	$(CC) $^ -o $@

pack:
	zip -r teodora.stroe2210.zip *

clean:
	rm -f $(TARGETS)
	
.PHONY: build clean
