/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badriano <badriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 11:35:17 by badriano          #+#    #+#             */
/*   Updated: 2025/10/16 13:49:20 by badriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main(void)
{
    try
    {
        Bureaucrat man = Bureaucrat("man2", 300);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << " in main" << std::endl;
    }
    return 0;
}