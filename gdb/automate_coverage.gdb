tar extended-remote :10001
load bubble.cov

b base.c:85
commands 1
    silent
    set $filename = tmp->info->filename
    set $dataBegin = buffer
    set $dataEnd = buffer + sizeInBytes
    eval "dump binary memory %s 0x%lx 0x%lx", $dataBegin, $dataEnd, $filename 
    eval "echo dump binary memory %s 0x%lx 0x%lx", $dataBegin, $dataEnd, $filename 
    echo \n
    c
end
c

