uv_install_link := if os() =~ "windows" {
  "powershell -ExecutionPolicy ByPass -c 'irm https://astral.sh/uv/install.ps1 | iex'"
} else {
  "curl -LsSf https://astral.sh/uv/install.sh | sh"
}

setup:
    @echo "Setting up {{GREEN + BOLD}}just{{NORMAL}} & {{YELLOW + BOLD}}python{{NORMAL}} interpreters..."
    -cargo install just
    if which uv > /dev/null; then \
      uv self update; \
    else \
      {{uv_install_link}}; \
    fi 
    -just system refreshenv

    @echo "{{GREEN + BOLD}}just{{NORMAL}} & {{YELLOW + BOLD}}python{{NORMAL}} interpreters setup complete."
    @echo "{{GREEN + BOLD}}just{{NORMAL}} version: $(just --version)"
    @echo "{{YELLOW + BOLD}}uv{{NORMAL}} version: $(uv --version)"

    @echo "{{YELLOW + BOLD}}TERMINAL RESTART REQUIRED AFTER SETUP{{NORMAL}}."
    @sleep 3
    @exit
  