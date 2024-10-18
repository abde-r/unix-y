/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_sort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-asri <ael-asri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:38:08 by ael-asri          #+#    #+#             */
/*   Updated: 2024/10/15 22:40:38 by ael-asri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ls.h"

int	reverse_compare_case_sensitive(const char	*a, const char	*b)
{
	char	lower_a;
	char	lower_b;

	while (*a && *b)
	{
		lower_a = ft_tolower(*a);
		lower_b = ft_tolower(*b);
		if (lower_a != lower_b)
			return (lower_b - lower_a);
		a++;
		b++;
	}
	return (*b - *a);
}

int	sort_state(t_list	*current, t_list	*next, int __reverse_flag_)
{
	int	_sort_stat;

	_sort_stat = -1;
	if (!__reverse_flag_)
		_sort_stat = compare_case_sensitive(current->content, \
		next->content);
	else if (__reverse_flag_ == 1)
		_sort_stat = reverse_compare_case_sensitive(current->content, \
		next->content);
	return (_sort_stat);
}

// void split_list(t_list *source, t_list **front, t_list **back) {
//     t_list *slow = source;
//     t_list *fast = source->next;

//     while (fast != NULL) {
//         fast = fast->next;
//         if (fast != NULL) {
//             slow = slow->next;
//             fast = fast->next;
//         }
//     }
//     *front = source;
//     *back = slow->next;
//     slow->next = NULL;
// }

// // Merge two sorted lists based on sorting state
// t_list *merge_sorted(t_list *a, t_list *b, int reverse_flag) {
//     t_list *result = NULL;

//     if (a == NULL) return b;
//     if (b == NULL) return a;

//     if (sort_state(a, b, reverse_flag) <= 0) {
//         result = a;
//         result->next = merge_sorted(a->next, b, reverse_flag);
//     } else {
//         result = b;
//         result->next = merge_sorted(a, b->next, reverse_flag);
//     }
//     return result;
// }

// // Recursive merge sort for linked lists
// void merge_sort(t_list **head, int reverse_flag) {
//     if (*head == NULL || (*head)->next == NULL) return;

//     t_list *a, *b;
//     split_list(*head, &a, &b);

//     // Recursively sort both halves
//     merge_sort(&a, reverse_flag);
//     merge_sort(&b, reverse_flag);

//     // Merge the two sorted halves
//     *head = merge_sorted(a, b, reverse_flag);
// }

// // Main sorting function with recursive subdirectory sorting
// void sort(t_list **head, int reverse_flag) {
//     // Sort the main list
//     merge_sort(head, reverse_flag);

//     // Sort each subdirectory recursively
//     t_list *current = *head;
//     while (current != NULL) {
//         if (current->subdirectory != NULL) {
//             sort(&current->subdirectory, reverse_flag);
//         }
//         current = current->next;
//     }
// }

// Sorting the list using bubble sort
void	sort(t_list	**head, int __reverse_flag_)
{
	t_list	*current;
	t_list	*next;
	int		swapped;

	if (!*head)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = *head;
		while (current->next != NULL)
		{
			next = current->next;
			if (sort_state(current, next, __reverse_flag_) > 0)
				swapped = swap_nodes(current, next);
			current = current->next;
		}
	}
	current = *head;
	while (current != NULL)
	{
		if (current->subdirectory != NULL)
			sort(&current->subdirectory, __reverse_flag_);
		current = current->next;
	}
}

// Recursive function to sort directories
// and their contents by modification time
// void	sort_recursive_by_time(t_list	**head, char	*path, int __flag_)
// {
// 	t_list	*current;
// 	char	*full_path;

// 	current = *head;
// 	if (!__flag_)
// 		sort_by_time(head, path);
// 	else if (__flag_ == 1)
// 		sort_by_access_time(head, path);
// 	while (current != NULL)
// 	{
// 		if (is_directory(current->content) && ft_strcmp(current->content, "."))
// 		{
// 			full_path = ft_strjoin(path, "/", current->content);
// 			sort_recursive_by_time(&(current->subdirectory), \
// 			full_path, __flag_);
// 			free(full_path);
// 		}
// 		current = current->next;
// 	}
// }

t_list	*merge_sorted(t_list	*left, t_list	*right, \
char	*path, int (*compare)(struct stat, struct stat))
{
	struct stat	stat_left;
	struct stat	stat_right;
	char		*full_path_left;
	char		*full_path_right;

	if (!left)
		return (right);
	if (!right)
		return (left);
	full_path_left = ft_strjoin(path, "/", left->content);
	full_path_right = ft_strjoin(path, "/", right->content);
	lstat(full_path_left, &stat_left);
	lstat(full_path_right, &stat_right);
	free(full_path_left);
	free(full_path_right);
	if (compare(stat_left, stat_right) <= 0)
	{
		left->next = merge_sorted(left->next, right, path, compare);
		return (left);
	}
	else
	{
		right->next = merge_sorted(left, right->next, path, compare);
		return (right);
	}
}

/*
	Split the list into two halves
	and recursively sort both halves
	then merge the sorted halves
*/
t_list	*merge_sort(t_list	*head, char	*path, \
int (*compare)(struct stat, struct stat))
{
	t_list	*left;
	t_list	*right;
	t_list	*slow;
	t_list	*fast;
	t_list	*mid;

	if (!head || !head->next)
		return (head);
	slow = head;
	fast = head->next;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	mid = slow->next;
	slow->next = NULL;
	left = merge_sort(head, path, compare);
	right = merge_sort(mid, path, compare);
	return (merge_sorted(left, right, path, compare));
}

int	compare_mtime(struct stat a, struct stat b)
{
	if (a.st_mtime < b.st_mtime)
		return (1);
	else
	{
		if (a.st_mtime > b.st_mtime)
			return (-1);
		return (0);
	}
}

int	compare_atime(struct stat a, struct stat b)
{
	if (a.st_atime < b.st_atime)
		return (1);
	else
	{
		if (a.st_atime > b.st_atime)
			return (-1);
		return (0);
	}
}

/*
	Select comparison function and 
	perform merge sort on the current directory
	then recursively sort subdirectories
*/
void	sort_time(t_list	**head, char	*path, int __flag_)
{
	t_list	*current;
	char	*full_path;
	int		(*compare)(struct stat, struct stat);

	if (!*head)
		return ;
	if (__flag_ == 1)
		compare = compare_atime;
	else
		compare = compare_mtime;
	*head = merge_sort(*head, path, compare);
	current = *head;
	while (current != NULL)
	{
		if (is_directory(current->content) && ft_strcmp(current->content, "."))
		{
			full_path = ft_strjoin(path, "/", current->content);
			sort_time(&(current->subdirectory), full_path, __flag_);
			free(full_path);
		}
		current = current->next;
	}
}
