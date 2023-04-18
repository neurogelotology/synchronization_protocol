function trgPulse(a,outpin)
    if ~isa(a,'arduino')
        error('first argument must be arduino object')
    end
    if ~isa(outpin,'char')
        error('second argument must be char')
    end
    trgWidth = 0.1; % [s]
    trgTime = tic;
    a.writeDigitalPin(outpin,1);
    while toc(trgTime) < trgWidth
        continue
    end
    a.writeDigitalPin(outpin,0);
end