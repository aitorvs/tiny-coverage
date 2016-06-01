tar extended-remote :10001
load bubble.cov

b base.c:85
commands 1
    silent
    set $filename = tmp->info-filename
    set $dataBegin = buffer
    set $dataEnd = buffer + sizeInBytes
    eval "dump binary memory [0x%lx - 0x%lx] to %s", $dataBegin, $dataEnd, $filename 
    echo dump binary memory $filename $dataBegin $dataEnd
    echo \n
    c
end
c

