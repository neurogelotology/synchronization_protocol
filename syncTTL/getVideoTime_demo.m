function timestamps = getVideoTime_demo(csvFilePath)
%{
    get frame timestamps [s] from video csv

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
    timestamps = T.Var1 * ns2s;

end