set unstable

[windows]
[script('powershell')]
@_refreshenv-ps:
    $env:Path=(
        [System.Environment]::GetEnvironmentVariable("Path","Machine"),
        [System.Environment]::GetEnvironmentVariable("Path","User")
    ) -match '.' -join ';'

[windows]
@refreshenv: _refreshenv-ps
    echo "Refreshing system's {{GREEN + BOLD}}PATH{{NORMAL}}..."

[linux]
@refreshenv:
    echo "Refreshing system's {{GREEN + BOLD}}PATH{{NORMAL}}..."
    -source ~/.bash_profile