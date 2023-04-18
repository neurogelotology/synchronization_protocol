function upTime = getVideoTTL_demo(csvFilePath)
%{
    get sync TTL rise timestamps [s] from video csv

    Dagher & Ishiyama (2023)
%}
    if ~nargin
        [csvFile,csvPath] = uigetfile('*.csv','Select video csv file');
        csvFilePath = [csvPath,csvFile];
    end
    if ~csvFilePath
        return % user cancel
    end
    
    T = readtable(csvFilePath);
    ns2s = 1e-9;
    upTime = T.Var1(find(diff(T.Var2) == 1) + 1) * ns2s;

end