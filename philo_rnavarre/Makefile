NAME 				= 	philo
SOURCE				= 	\
						main.c 			\
						libft_utils.c 	\


SRCS_DIR 			= 	src
OBJS_DIR 			= 	obj
DEPS_DIR 			=	obj
INCS_DIR 			= 	inc

SRCS 				=	$(addprefix $(SRCS_DIR)/, $(SOURCE))
OBJS				= 	$(addprefix $(OBJS_DIR)/, $(SOURCE:.c=.o))
DEPS 				=	$(addprefix $(DEPS_DIR)/, $(SOURCE:.c=.d))

CC 					= 	clang
RM 					= 	rm -rfv
MKDIR 				= 	mkdir -p

WARNING_FLAGS 		= 	-Wall -Wextra -Werror
INCLUDES 			= 	$(addprefix -I, $(INCS_DIR))
SANITIZE 			=	-fsanitize=address -g3
DEPENDENCE_FLAGS  	= 	-MMD

LDFLAGS 			=
CFLAGS 				= 	$(WARNING_FLAGS) $(INCLUDES) $(DEPENDENCE_FLAGS)

all: 			$(NAME)

$(OBJS_DIR)/%.o: 	$(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): 		$(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

fclean: 		clean
	$(RM) $(NAME)
.PHONY:  		fclean

clean:
	$(RM) $(OBJS_DIR)
.PHONY:  		clean

sanitize:		CFLAGS += $(SANITIZE)
sanitize:		LDFLAGS += $(SANITIZE)
sanitize: 		all
.PHONY:  		sanitize

run: 			all
	./$(NAME) 4 310 210 100
.PHONY:  		run

runs:			sanitize run
.PHONY:  		runs

-include: 		$(DEPS)
