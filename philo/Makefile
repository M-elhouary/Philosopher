NAME = philo

	CC = cc

		FLAGS = -Wall - Wextra - Werror

										SRC = check_validation_of_arg.c
												main_philo.c
													utils.c
														creat.c
															fill_and_initial.c
																monitor.c
																	simulation.c

																		OBJ = $(SRC
																				:.c =.o)

																					all : $(NAME)

																							$(NAME)
	: $(OBJ)
			$(CC) $(FLAGS) $(OBJ) -
		o $(NAME)

			clean : rm -
					rf $(OBJ)

						fclean : clean
									rm -
								rf $(NAME)

									re : fclean all

											.PHONY : all clean fclean re
