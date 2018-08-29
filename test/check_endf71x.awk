#! /bin/awk -f

BEGIN {
    id = 0;
}

/^#/ { 
    next;
}

/^ids:/ {
    id = 1;
}

/^%%/ {
    id = 0;
}

id == 1 {
    # Calculate s, z, a
    s = int($1/1000000);
    za = $1 - s*1000000;
    z = int(za/1000);
    a = za % 1000;

    # Calculate HRT representation
    
    hrt = z*1000 + a;
    if (s) {
        hrt += 300 + 100*s;
    }

    if (match($2, hrt) != 1) {
        print $0;
    } else {
        print $0, "ok";
    }
}
