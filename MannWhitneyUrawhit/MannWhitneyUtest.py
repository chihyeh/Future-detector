import ROOT

def histmaker(S):
  D = S*1
  D.sort()
  h_BinCenter = []
  h_BinContent = []
  i = 0
  while (i < len(D)):
    h_BinCenter.append(D[i])
    h_BinContent.append(D.count(h_BinCenter[-1]))
    i = i + h_BinContent[-1]
  return h_BinCenter, h_BinContent

def mannWUrawdat(S1, S2): #for raw python lists
  h1_BinCenter, h1_BinContent = histmaker(S1)
  h2_BinCenter, h2_BinContent = histmaker(S2)
  I1 = len(S1)
  I2 = len(S2)
  U = -0.5*I1*(I1 + 1)
  irank = 0
  for i in range(len(h1_BinCenter)):
    rank = irank
    for j in range(len(h2_BinCenter)):
    	if (h1_BinCenter[i] > h2_BinCenter[j]): rank = rank + h2_BinContent[j]
    	else:
      		rank = rank + 0.5*h2_BinContent[j]*int(h1_BinCenter[i] == h2_BinCenter[j])
    	break
    rank = rank + 0.5*(h1_BinContent[i] + 1)
    U = U + rank*h1_BinContent[i]
    irank =  irank + h1_BinContent[i]
  return U/(I1*I2)

def mannWU(h1, h2): #for TH1s
  n1 = h1.GetSize()
  n2 = h2.GetSize()
  I1 = h1.Integral() + h1.GetBinContent(0) + h1.GetBinContent(n1-1) #adding the underflow and overflow bins by hand
  I2 = h2.Integral() + h2.GetBinContent(0) + h2.GetBinContent(n2-1)
  print I1, I2
  U = -0.5*I1*(I1 + 1)
  irank = 0
  for i in range(n1):
    rank = irank
    for j in range(n2):
      if (h1.GetBinCenter(i) > h2.GetBinCenter(j)): rank = rank + h2.GetBinContent(j)
      else:  
      	rank = rank + 0.5*h2.GetBinContent(j)*int(h1.GetBinCenter(i) == h2.GetBinCenter(j))
        break
    rank = rank + 0.5*(h1.GetBinContent(i) + 1)
    U = U + rank*h1.GetBinContent(i)
    irank =  irank + h1.GetBinContent(i)
  return U/(I1*I2)

def main():
  #f1 = ROOT.TFile.Open("Events.root", 'READ')
  #h1 = f1.Get('events')
  #f2 = ROOT.TFile.Open("Eventsshifted.root", 'READ')
  #h2 = f2.Get('events')
  #f3 = ROOT.TFile.Open("Eventsoverlaped.root", 'READ')
  #h3 = f3.Get('events')
  #print mannWU(h1, h1)
  #print mannWU(h2, h2)
  #print mannWU(h2, h1)
  #print mannWU(h2, h2)
  #print mannWU(h1, h3)
  #print mannWU(h3, h1)
  #print mannWU(h3, h2)
  #print mannWU(h2, h3)
  fA = ROOT.TFile.Open("A.root", 'READ')
  hA = fA.Get('events')
  fB = ROOT.TFile.Open("B.root", 'READ')
  hB = fB.Get('events')
  print mannWU(hA, hB)
  #print mannWU(hB, hA)

if __name__ == '__main__':
  main()
