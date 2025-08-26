import '.just/modules.just'

default:
    @echo "Usage: just <command> [options]"
    @just --list

v +FLAGS:
    @just version worker {{ FLAGS }}
