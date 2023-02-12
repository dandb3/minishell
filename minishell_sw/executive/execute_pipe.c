/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunwsong <sunwsong@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:58:07 by sunwsong          #+#    #+#             */
/*   Updated: 2023/02/12 13:50:23 by sunwsong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	close_all(t_pipe_info *info)
{
	int	idx;

	idx = -1;
	while (++idx < info->process_cnt - 1)
	{
		if (close(info->fds[idx][0]) < 0)
			perror_msg(NULL, 1);
		if (close(info->fds[idx][1]) < 0)
			perror_msg(NULL, 1);
	}
}

static void	parent_process(t_pipe_info *info)
{
	int	status;
	int	idx;

	idx = -1;
	close_all(info);
	while (++idx < info->process_cnt)
	{
		if (wait(&status) < 0)
			perror_msg(NULL, 1);
	}
	//here_doc 리스트 순회하면서 unlink를 해주는데 에러 처리는 하지 말 것.
	if ((status << 24) != 0)
		exit((status << 24 >> 24) + 128);
	else
		exit(status >> 8);
}

static void	child_process(t_pipe_info *info, int idx)
{
	t_list	*lst;
	int		fd_stdin;

	lst = NULL;
	fd_stdin = dup(STDIN_FILENO);
	if (fd_stdin < 0)
		perror_msg(NULL, 1);
	if (idx != 0)
		dup2(info->fds[idx - 1][0], STDIN_FILENO);
	if (idx + 1 != info->process_cnt)
		dup2(info->fds[idx][1], STDIN_FILENO);
	close_all(info);
	if (close(fd_stdin) < 0)
		perror_msg(NULL, 1);
	// 파일 리스트를 순회하면서 쭉 파일 열고 dup2 수행.
	// do_builtin
	// builtin이 성공하면 exit()
	// execve
	// perror_msg(파일 이름, 126);
}

/*-------malloc on "info" finished-------*/
void	pipe_process(t_pipe_info *info)
{
	pid_t	pid;
	int		idx;

	//here_doc 지울 거 리스트로 저장
	idx = -1;
	while (++idx < info->process_cnt - 1)
		if (pipe(info->fds[idx]) < 0)
			perror_msg(NULL, 1);
	idx = -1;
	while (++idx < info->process_cnt)
	{
		pid = fork();
		if (pid < 0)
			perror_msg(NULL, 1);
		if (pid == 0)
			break ;
	}
	if (pid == 0)
		child_process(info, idx);
	else
		parent_process(info); //here_doc 지울 거 리스트 인자로 전달
}
