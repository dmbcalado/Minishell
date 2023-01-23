<h1><em>Minishell</em><strong><em> (grade : 100)</em></strong></h1>
<div align="center"><br /><img src="https://user-images.githubusercontent.com/76601369/110706242-77158d00-81ef-11eb-8085-5da6f0988553.jpg" alt="https://user-images.githubusercontent.com/76601369/110706242-77158d00-81ef-11eb-8085-5da6f0988553.jpg" width="400" height="200" /></div>
<p><strong>This project has the goal to create a replica of the GNU Bash Shell, that besides the required built in functions, runs and redirects every command in a child process (runs by executing execve() function).</strong></p>
<p> The required builtin commands where:</p>
<ul style="list-style-type: square;">
  <li><strong>env</strong> : We needed to extract the environment variables from the computer and create our own list, also increasing the $SHLVL every time we open a new minishell inside minishell.</li>
  <li><strong>export</strong> : export should let us include a new environment variable and handle it the same way as the GNU Bash. </li>
<li><strong>unset</strong> : unset should let us erase an environment variable and handle it the same way as the GNU Bash (with full permissions). 
<li><strong>cd</strong> : Should perform every cd operation.</li>
<li><strong>pwd</strong> : Should perform the same way as pwd from GNU Bash.</li>

<li><strong>exit</strong> : Enable the user to leave the shell and returning an exit code that would tell the error.</li>
