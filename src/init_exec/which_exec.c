#include "executing.h"
#include "parsing.h"

// void	execution(t_cmd *cmd)
// {
// 	if (premier token est un builtin)
// 		execute_builtin(...);
// 	else
// 		execute(...);
// 	if (cmd->pipe)
// 		execute_pipe(cmd->pipe);
// }

void	parent(t_command *cmd, t_exec *exec)
{
	static int	pipe_fds[2];

	if (cmd->next)
		parent(cmd->next, exec);
	if (cmd->index != exec->cmd_nbr - 1)
		if (pipe(pipe_fds) == -1)
			ft_error();
	runner(cmd, exec, pipe_fds);
	if (!(cmd->index))
	{
		close_pipe(cmd);
		hold_on(exec->pid, &(exec->status));
		if (WEXITSTATUS(exec->status))
			return_code(exec);
	}
}
