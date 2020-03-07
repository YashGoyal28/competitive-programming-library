---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: old/popen2.inc.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#149603e6c03516362a8da23f624db945">old</a>
* <a href="{{ site.github.repository_url }}/blob/master/old/popen2.inc.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-08 18:35:19+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
pid_t popen2(const char *command, int *fd_r, int *fd_w) {
    constexpr int READ = 0;
    constexpr int WRITE = 1;
    int p_stdin[2], p_stdout[2];
    if (pipe(p_stdin) != 0 or pipe(p_stdout) != 0) return -1;
    pid_t pid = fork();
    if (pid < 0) return -1;
    if (pid == 0) {
        close(p_stdin[WRITE]);
        dup2(p_stdin[READ], STDIN_FILENO);
        close(p_stdout[READ]);
        dup2(p_stdout[WRITE], STDOUT_FILENO);
        execl("/bin/sh", "sh", "-c", command, NULL);
        exit(1);
    } else {
        if (fd_r == NULL) {
            close(p_stdin[WRITE]);
        } else {
            *fd_r = p_stdin[WRITE];
        }
        if (fd_w == NULL) {
            close(p_stdout[READ]);
        } else {
            *fd_w = p_stdout[READ];
        }
        return pid;
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "old/popen2.inc.cpp"
pid_t popen2(const char *command, int *fd_r, int *fd_w) {
    constexpr int READ = 0;
    constexpr int WRITE = 1;
    int p_stdin[2], p_stdout[2];
    if (pipe(p_stdin) != 0 or pipe(p_stdout) != 0) return -1;
    pid_t pid = fork();
    if (pid < 0) return -1;
    if (pid == 0) {
        close(p_stdin[WRITE]);
        dup2(p_stdin[READ], STDIN_FILENO);
        close(p_stdout[READ]);
        dup2(p_stdout[WRITE], STDOUT_FILENO);
        execl("/bin/sh", "sh", "-c", command, NULL);
        exit(1);
    } else {
        if (fd_r == NULL) {
            close(p_stdin[WRITE]);
        } else {
            *fd_r = p_stdin[WRITE];
        }
        if (fd_w == NULL) {
            close(p_stdout[READ]);
        } else {
            *fd_w = p_stdout[READ];
        }
        return pid;
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

