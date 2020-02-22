# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldevelle <ldevelle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/12 15:04:16 by ldevelle          #+#    #+#              #
#    Updated: 2020/02/22 19:18:41 by ldevelle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= ft_ls
TESTEUR = test

CC 		= gcc
AR		= ar -rcs

LIB_PRJCT = n

CFLAGS	= -Wall -Wextra -Werror

##############################################################################
##############################################################################
##																			##
##									----									##
##								 TO_CHANGE									##
##									----									##
##																			##
##############################################################################
##############################################################################

login 		=	ldevelle\
				ymekraou

LIB_DIR		=	./libft
LIB			=	$(LIB_DIR)/libft.a -lm

HEAD_DIR 	= 	./includes/
HEADERS		=	$(AUTO_HEAD)\
				head.h

HEADERS_DIRECTORIES = -I./$(HEAD_DIR) -I./$(LIB_DIR)/includes

# HEAD_PATH	=	$(HEAD_DIR)/$(HEAD)

DIR_OBJ 	=	./objs/

##########################
##						##
##	   ARCHITECTURE		##
##						##
##########################

MAIN_FOLD 	=	$(shell find srcs -maxdepth 1 -type d | grep '/' | cut -d '/' -f 2)
MASTER		= 	srcs/
$(shell mkdir -p $(MASTER))
AUTO_HEAD	=	$(MAIN_FOLD:%=auto/auto_%.h)

HEAD		=	$(HEADERS:%=$(HEAD_DIR)%)

mk			=	./mk_dependencies

mk_d		= 	$(mk)/DIR/
mk_s		= 	$(mk)/SRC/
mk_p		= 	$(mk)/PAT/

include_dir	=	$(MAIN_FOLD:%=$(mk_d)dir_%.mk)
include_dir	+=	$(mk_d)dir_.mk
include_pat	=	$(MAIN_FOLD:%=$(mk_p)pat_%.mk)
include_pat	+=	$(mk_p)pat_.mk
include_src	=	$(MAIN_FOLD:%=$(mk_s)src_%.mk)
include_src	+=	$(mk_s)src_.mk

include_dep	=	$(include_src) $(include_pat) $(include_dir)

SRC =
PAT =
DIR =

$(shell mkdir -p $(mk) $(mk_d) $(mk_s) $(mk_p))
$(shell touch $(include_dep))
include $(include_dep)

OBJ 	= $(PAT:%.c=%.o)
OBJS	= $(PAT:$(MASTER)%.c=$(DIR_OBJ)%.o)

ARG 	?= ldevelle

##########################
##						##
##		 COLORS			##
##						##
##########################
UNAME := $(shell uname)
ifeq ($(UNAME),Linux)
RED     	= \e[31m
GREEN   	= \e[32m
YELLOW  	= \e[33m
BLUE		= \e[34m
MAGENTA		= \e[35m
CYAN		= \e[36m
END     	= \e[0m
update_head	=	$(MAIN_FOLD:%=sh scripts/get_protos_linux.sh % $(MASTER);)
update_head	+=	sh scripts/get_protos_linux.sh '' $(MASTER) '' '-depth 1';
update_dep	=	$(MAIN_FOLD:%=sh scripts/get_mk_srcs_linux.sh % $(MASTER);)
update_dep	+=	sh scripts/get_mk_srcs_linux.sh '' $(MASTER) '' '-depth 1';
else
RED     	= \x1b[31m
GREEN   	= \x1b[32m
YELLOW  	= \x1b[33m
BLUE		= \x1b[34m
MAGENTA		= \x1b[35m
CYAN		= \x1b[36m
END     	= \x1b[0m
update_head	=	$(MAIN_FOLD:%=sh scripts/get_protos.sh % $(MASTER);)
update_head	+=	sh scripts/get_protos.sh '' $(MASTER) '' '-d 1';
update_dep	=	$(MAIN_FOLD:%=sh scripts/get_mk_srcs.sh % $(MASTER);)
update_dep	+=	sh scripts/get_mk_srcs.sh '' $(MASTER) '' '-d 1';
endif

COM_COLOR   = $(BLUE)
OBJ_COLOR   = $(CYAN)
OK_COLOR    = $(GREEN)
ERROR_COLOR = $(RED)
WARN_COLOR  = $(YELLOW)
NO_COLOR    = $(END)

OK_STRING    	= [OK]
ERROR_STRING 	= [ERROR]
WARN_STRING  	= [WARNING]
COM_STRING   	= Compiling

REQUEST 		= 'read -p "Enter a commit message:	" pwd && echo $$pwd'
COMMIT_MESSAGE ?= $(shell bash -c $(REQUEST))

ifeq ($(f), no)
CFLAGS 		+=
VALGRIND 	=
else ifeq ($(f), n)
CFLAGS 		=
VALGRIND 	=
else ifeq ($(f), f)
CFLAGS 		+=  -fsanitize=address,undefined -g3
VALGRIND 	=
else ifeq ($(f), v)
CFLAGS 		+= -g3
SHOW_LEAK 	= --show-leak-kinds=definite
VALGRIND 	= valgrind --track-origins=yes --leak-check=full $(SHOW_LEAK)
else ifeq ($(f), h)
CFLAGS 		= -fsanitize=address,undefined -g3 -pedantic\
-ansi -O2 -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int\
-Werror-implicit-function-declaration -Wmain -Wparentheses -Wsequence-point\
-Wreturn-type -Wswitch -Wtrigraphs -Wunused -Wuninitialized -Wunknown-pragmas\
-Wfloat-equal -Wundef -Wshadow -Wpointer-arith -Wbad-function-cast\
-Wwrite-strings -Wconversion -Wsign-compare -Waggregate-return\
-Wstrict-prototypes -Wmissing-prototypes -Wmissing-declarations\
-Wmissing-noreturn -Wformat -Wmissing-format-attribute\
-Wno-deprecated-declarations -Wpacked -Wredundant-decls -Wnested-externs\
-Winline -Wlong-long -Wunreachable-code
VALGRIND 	=
endif

FETCH_MODULES	= $(shell grep "url" .gitmodules | cut -d '=' -f 2)

define run_and_test
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
	$(1) 2> $@.log; \
	RESULT=$$?; \
	if [ $$RESULT -ne 0 ]; then \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
	elif [ -s $@.log ]; then \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
	else  \
	printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
	fi; \
	cat $@.log; \
	rm -f $@.log; \
	exit $$RESULT
endef
# @$(call run_and_test, $(CC) $(CFLAGS) -o $(NAME) $(LIB) -I./$(HEAD_DIR) $(OBJS))
# @$(call run_and_test, $(CC) $(CFLAGS) $(LIB) -I$(HEAD_DIR) -o $@ -c $<)

##############################################################################
##############################################################################
##																			##
##									-----									##
##									RULES									##
##									-----									##
##																			##
##############################################################################
##############################################################################

##########################
##						##
##		  BASIC			##
##						##
##########################

all :		$(NAME) auteur $(DIR_OBJ)

ifeq ($(LIB_PRJCT), y)
$(NAME):	$(OBJS) $(HEAD_DIR)
	@$(call run_and_test, $(AR) $(NAME) $(OBJS))
else
$(NAME):	$(LIB) $(OBJS) $(HEAD_DIR)
	@$(call run_and_test, $(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIB) $(HEADERS_DIRECTORIES))
endif

$(DIR_OBJ)%.o:$(MASTER)%.c $(HEAD) Makefile
	@$(call run_and_test, $(CC) $(CFLAGS) $(HEADERS_DIRECTORIES) -o $@ -c $<)

$(LIB): FORCE
		@$(MAKE) -C $(LIB_DIR)

clean :
	@rm -f $(OBJS)
	@echo "\$(YELLOW)$(NAME) objs \$(END)\\thas been \$(GREEN)\\t\\t\\t  $@\$(END)"

fclean : clean
	@rm -f $(NAME)
	@echo "\$(YELLOW)$(NAME) \$(END)\\thas been \$(GREEN)\\t\\t\\t  $@\$(END)"

re : fclean all

rere :
	@$(MAKE) re -C $(LIB_DIR)
	@$(MAKE) re


##############################################################################
##############################################################################
##																			##
##									-----									##
##									BONUS									##
##									-----									##
##																			##
##############################################################################
##############################################################################

auteur :
		@echo $(login) > auteur

$(DIR_OBJ) :
		@mkdir -p $(DIR_OBJ)

t	:	all
		$(CC) $(CFLAGS) -I$(HEAD_DIR) $(NAME) main.c -o $(TESTEUR)
		$(VALGRIND) ./$(TESTEUR) "$(ARG)"

unit_test :

big :
n ?= 10
n=$(n); \
while [ $${n} -gt 0 ] ; do \
    $(MAKE) unit_test \
done; \
true

# last :	all
# 		@./$(NAME) $(shell cat tests/last)


# @$(CC) $(CFLAGS) ./srcs/show_stats.c $(LIB) -o stats
# @./stats $(nb)

DIR_PREP = $(shell find $(MASTER) -type d -exec echo {} \; | sed 's~$(MASTER)~$(DIR_OBJ)~g')
# GIT_PREP = $(shell find $(MASTER) -type d -exec echo {} \; | sed 's~$(MASTER)~$(DIR_OBJ)~g' | sed 's~$~\.gitkeep$~g')

git :
		@git add -A
		@git status
		@git commit -am "$(COMMIT_MESSAGE)"
		@git push

file : 	srcs head
		@$(MAKE)

srcs :	object_ready
		@rm -rf $(mk_d) $(mk_s) $(mk_p)
		@mkdir $(mk_d) $(mk_s) $(mk_p)
		@$(update_dep)
		@echo "\$(YELLOW)automatic sources\$(END)\\thas been \$(GREEN)\\t\\t  created\$(END)"

object_ready :	$(DIR_OBJ)
		@rm -rf $(DIR_OBJ)/*
		@mkdir -p $(DIR_PREP)
		@find $(DIR_OBJ) -type d -exec touch {}/.gitkeep \;
		@echo "\$(YELLOW)objects paths\$(END)\\t\\thas been \$(GREEN)\\t\\t  created\$(END)"

head :	auto_dir
		@$(update_head)
		@sh scripts/get_master_head.sh $(HEAD_DIR)
		@echo "\$(YELLOW)automatic headers\$(END)\\thas been \$(GREEN)\\t\\t  created\$(END)"

auto_dir :	head
		@mkdir -p $(HEAD_DIR)auto

modules :
		git clone $(FETCH_MODULES)

FORCE:

##########################
##						##
##		 .PHONY			##
##						##
##########################

.PHONY : all clean fclean re git file object_ready check FORCE
