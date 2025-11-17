import os
import strutils
import sequtils

proc ok() =
    echo "ok"

proc runc(command : string): int = 
    let r = execShellCmd(command)
    if r != 0:
        echo "There was an error running:"
        echo "\t" & command
        echo "Exit code: ", r
    else:
        ok()

proc runcs(commands: seq[string]): int = 
    return runc(commands.filter(proc (s: string): bool = s.len > 0).join(" && "))


export runcs, runc, ok