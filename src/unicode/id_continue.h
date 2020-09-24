int is_unicode_id_continue(uint32_t c){
   if(c < 0xA7C2){
      if(c < 0x0E84){
         if(c < 0x0AAA){
            if(c < 0x07FA){
               if(c < 0x03F7){
                  if(c < 0x02E0){
                     if(c < 0x00B7){
                        if(c < 0x0061){
                           if(c < 0x005F){
                              if(c < 0x0041){
                                 return (c >= 0x0030 && c <= 0x0039);
                              } else {
                                 return (c >= 0x0041 && c <= 0x005A);
                              }
                           } else {
                              return (c >= 0x005F && c <= 0x005F);
                           }
                        } else {
                           if(c < 0x00B5){
                              if(c < 0x00AA){
                                 return (c >= 0x0061 && c <= 0x007A);
                              } else {
                                 return (c >= 0x00AA && c <= 0x00AA);
                              }
                           } else {
                              return (c >= 0x00B5 && c <= 0x00B5);
                           }
                        }
                     } else {
                        if(c < 0x00D8){
                           if(c < 0x00C0){
                              if(c < 0x00BA){
                                 return (c >= 0x00B7 && c <= 0x00B7);
                              } else {
                                 return (c >= 0x00BA && c <= 0x00BA);
                              }
                           } else {
                              return (c >= 0x00C0 && c <= 0x00D6);
                           }
                        } else {
                           if(c < 0x02C6){
                              if(c < 0x00F8){
                                 return (c >= 0x00D8 && c <= 0x00F6);
                              } else {
                                 return (c >= 0x00F8 && c <= 0x02C1);
                              }
                           } else {
                              return (c >= 0x02C6 && c <= 0x02D1);
                           }
                        }
                     }
                  } else {
                     if(c < 0x037F){
                        if(c < 0x0300){
                           if(c < 0x02EE){
                              if(c < 0x02EC){
                                 return (c >= 0x02E0 && c <= 0x02E4);
                              } else {
                                 return (c >= 0x02EC && c <= 0x02EC);
                              }
                           } else {
                              return (c >= 0x02EE && c <= 0x02EE);
                           }
                        } else {
                           if(c < 0x037A){
                              if(c < 0x0376){
                                 return (c >= 0x0300 && c <= 0x0374);
                              } else {
                                 return (c >= 0x0376 && c <= 0x0377);
                              }
                           } else {
                              return (c >= 0x037A && c <= 0x037D);
                           }
                        }
                     } else {
                        if(c < 0x038E){
                           if(c < 0x038C){
                              if(c < 0x0386){
                                 return (c >= 0x037F && c <= 0x037F);
                              } else {
                                 return (c >= 0x0386 && c <= 0x038A);
                              }
                           } else {
                              return (c >= 0x038C && c <= 0x038C);
                           }
                        } else {
                           if(c < 0x03A3){
                              return (c >= 0x038E && c <= 0x03A1);
                           } else {
                              return (c >= 0x03A3 && c <= 0x03F5);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x05EF){
                     if(c < 0x0591){
                        if(c < 0x0531){
                           if(c < 0x048A){
                              if(c < 0x0483){
                                 return (c >= 0x03F7 && c <= 0x0481);
                              } else {
                                 return (c >= 0x0483 && c <= 0x0487);
                              }
                           } else {
                              return (c >= 0x048A && c <= 0x052F);
                           }
                        } else {
                           if(c < 0x0560){
                              if(c < 0x0559){
                                 return (c >= 0x0531 && c <= 0x0556);
                              } else {
                                 return (c >= 0x0559 && c <= 0x0559);
                              }
                           } else {
                              return (c >= 0x0560 && c <= 0x0588);
                           }
                        }
                     } else {
                        if(c < 0x05C4){
                           if(c < 0x05C1){
                              if(c < 0x05BF){
                                 return (c >= 0x0591 && c <= 0x05BD);
                              } else {
                                 return (c >= 0x05BF && c <= 0x05BF);
                              }
                           } else {
                              return (c >= 0x05C1 && c <= 0x05C2);
                           }
                        } else {
                           if(c < 0x05D0){
                              if(c < 0x05C7){
                                 return (c >= 0x05C4 && c <= 0x05C5);
                              } else {
                                 return (c >= 0x05C7 && c <= 0x05C7);
                              }
                           } else {
                              return (c >= 0x05D0 && c <= 0x05EA);
                           }
                        }
                     }
                  } else {
                     if(c < 0x06EA){
                        if(c < 0x066E){
                           if(c < 0x0620){
                              if(c < 0x0610){
                                 return (c >= 0x05EF && c <= 0x05F2);
                              } else {
                                 return (c >= 0x0610 && c <= 0x061A);
                              }
                           } else {
                              return (c >= 0x0620 && c <= 0x0669);
                           }
                        } else {
                           if(c < 0x06DF){
                              if(c < 0x06D5){
                                 return (c >= 0x066E && c <= 0x06D3);
                              } else {
                                 return (c >= 0x06D5 && c <= 0x06DC);
                              }
                           } else {
                              return (c >= 0x06DF && c <= 0x06E8);
                           }
                        }
                     } else {
                        if(c < 0x074D){
                           if(c < 0x0710){
                              if(c < 0x06FF){
                                 return (c >= 0x06EA && c <= 0x06FC);
                              } else {
                                 return (c >= 0x06FF && c <= 0x06FF);
                              }
                           } else {
                              return (c >= 0x0710 && c <= 0x074A);
                           }
                        } else {
                           if(c < 0x07C0){
                              return (c >= 0x074D && c <= 0x07B1);
                           } else {
                              return (c >= 0x07C0 && c <= 0x07F5);
                           }
                        }
                     }
                  }
               }
            } else {
               if(c < 0x09E6){
                  if(c < 0x098F){
                     if(c < 0x08B6){
                        if(c < 0x0840){
                           if(c < 0x0800){
                              if(c < 0x07FD){
                                 return (c >= 0x07FA && c <= 0x07FA);
                              } else {
                                 return (c >= 0x07FD && c <= 0x07FD);
                              }
                           } else {
                              return (c >= 0x0800 && c <= 0x082D);
                           }
                        } else {
                           if(c < 0x08A0){
                              if(c < 0x0860){
                                 return (c >= 0x0840 && c <= 0x085B);
                              } else {
                                 return (c >= 0x0860 && c <= 0x086A);
                              }
                           } else {
                              return (c >= 0x08A0 && c <= 0x08B4);
                           }
                        }
                     } else {
                        if(c < 0x0966){
                           if(c < 0x08E3){
                              if(c < 0x08D3){
                                 return (c >= 0x08B6 && c <= 0x08C7);
                              } else {
                                 return (c >= 0x08D3 && c <= 0x08E1);
                              }
                           } else {
                              return (c >= 0x08E3 && c <= 0x0963);
                           }
                        } else {
                           if(c < 0x0985){
                              if(c < 0x0971){
                                 return (c >= 0x0966 && c <= 0x096F);
                              } else {
                                 return (c >= 0x0971 && c <= 0x0983);
                              }
                           } else {
                              return (c >= 0x0985 && c <= 0x098C);
                           }
                        }
                     }
                  } else {
                     if(c < 0x09C7){
                        if(c < 0x09B2){
                           if(c < 0x09AA){
                              if(c < 0x0993){
                                 return (c >= 0x098F && c <= 0x0990);
                              } else {
                                 return (c >= 0x0993 && c <= 0x09A8);
                              }
                           } else {
                              return (c >= 0x09AA && c <= 0x09B0);
                           }
                        } else {
                           if(c < 0x09BC){
                              if(c < 0x09B6){
                                 return (c >= 0x09B2 && c <= 0x09B2);
                              } else {
                                 return (c >= 0x09B6 && c <= 0x09B9);
                              }
                           } else {
                              return (c >= 0x09BC && c <= 0x09C4);
                           }
                        }
                     } else {
                        if(c < 0x09DC){
                           if(c < 0x09D7){
                              if(c < 0x09CB){
                                 return (c >= 0x09C7 && c <= 0x09C8);
                              } else {
                                 return (c >= 0x09CB && c <= 0x09CE);
                              }
                           } else {
                              return (c >= 0x09D7 && c <= 0x09D7);
                           }
                        } else {
                           if(c < 0x09DF){
                              return (c >= 0x09DC && c <= 0x09DD);
                           } else {
                              return (c >= 0x09DF && c <= 0x09E3);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x0A3E){
                     if(c < 0x0A13){
                        if(c < 0x0A01){
                           if(c < 0x09FE){
                              if(c < 0x09FC){
                                 return (c >= 0x09E6 && c <= 0x09F1);
                              } else {
                                 return (c >= 0x09FC && c <= 0x09FC);
                              }
                           } else {
                              return (c >= 0x09FE && c <= 0x09FE);
                           }
                        } else {
                           if(c < 0x0A0F){
                              if(c < 0x0A05){
                                 return (c >= 0x0A01 && c <= 0x0A03);
                              } else {
                                 return (c >= 0x0A05 && c <= 0x0A0A);
                              }
                           } else {
                              return (c >= 0x0A0F && c <= 0x0A10);
                           }
                        }
                     } else {
                        if(c < 0x0A35){
                           if(c < 0x0A32){
                              if(c < 0x0A2A){
                                 return (c >= 0x0A13 && c <= 0x0A28);
                              } else {
                                 return (c >= 0x0A2A && c <= 0x0A30);
                              }
                           } else {
                              return (c >= 0x0A32 && c <= 0x0A33);
                           }
                        } else {
                           if(c < 0x0A3C){
                              if(c < 0x0A38){
                                 return (c >= 0x0A35 && c <= 0x0A36);
                              } else {
                                 return (c >= 0x0A38 && c <= 0x0A39);
                              }
                           } else {
                              return (c >= 0x0A3C && c <= 0x0A3C);
                           }
                        }
                     }
                  } else {
                     if(c < 0x0A66){
                        if(c < 0x0A51){
                           if(c < 0x0A4B){
                              if(c < 0x0A47){
                                 return (c >= 0x0A3E && c <= 0x0A42);
                              } else {
                                 return (c >= 0x0A47 && c <= 0x0A48);
                              }
                           } else {
                              return (c >= 0x0A4B && c <= 0x0A4D);
                           }
                        } else {
                           if(c < 0x0A5E){
                              if(c < 0x0A59){
                                 return (c >= 0x0A51 && c <= 0x0A51);
                              } else {
                                 return (c >= 0x0A59 && c <= 0x0A5C);
                              }
                           } else {
                              return (c >= 0x0A5E && c <= 0x0A5E);
                           }
                        }
                     } else {
                        if(c < 0x0A8F){
                           if(c < 0x0A85){
                              if(c < 0x0A81){
                                 return (c >= 0x0A66 && c <= 0x0A75);
                              } else {
                                 return (c >= 0x0A81 && c <= 0x0A83);
                              }
                           } else {
                              return (c >= 0x0A85 && c <= 0x0A8D);
                           }
                        } else {
                           if(c < 0x0A93){
                              return (c >= 0x0A8F && c <= 0x0A91);
                           } else {
                              return (c >= 0x0A93 && c <= 0x0AA8);
                           }
                        }
                     }
                  }
               }
            }
         } else {
            if(c < 0x0C46){
               if(c < 0x0B66){
                  if(c < 0x0B0F){
                     if(c < 0x0AD0){
                        if(c < 0x0ABC){
                           if(c < 0x0AB5){
                              if(c < 0x0AB2){
                                 return (c >= 0x0AAA && c <= 0x0AB0);
                              } else {
                                 return (c >= 0x0AB2 && c <= 0x0AB3);
                              }
                           } else {
                              return (c >= 0x0AB5 && c <= 0x0AB9);
                           }
                        } else {
                           if(c < 0x0ACB){
                              if(c < 0x0AC7){
                                 return (c >= 0x0ABC && c <= 0x0AC5);
                              } else {
                                 return (c >= 0x0AC7 && c <= 0x0AC9);
                              }
                           } else {
                              return (c >= 0x0ACB && c <= 0x0ACD);
                           }
                        }
                     } else {
                        if(c < 0x0AF9){
                           if(c < 0x0AE6){
                              if(c < 0x0AE0){
                                 return (c >= 0x0AD0 && c <= 0x0AD0);
                              } else {
                                 return (c >= 0x0AE0 && c <= 0x0AE3);
                              }
                           } else {
                              return (c >= 0x0AE6 && c <= 0x0AEF);
                           }
                        } else {
                           if(c < 0x0B05){
                              if(c < 0x0B01){
                                 return (c >= 0x0AF9 && c <= 0x0AFF);
                              } else {
                                 return (c >= 0x0B01 && c <= 0x0B03);
                              }
                           } else {
                              return (c >= 0x0B05 && c <= 0x0B0C);
                           }
                        }
                     }
                  } else {
                     if(c < 0x0B47){
                        if(c < 0x0B32){
                           if(c < 0x0B2A){
                              if(c < 0x0B13){
                                 return (c >= 0x0B0F && c <= 0x0B10);
                              } else {
                                 return (c >= 0x0B13 && c <= 0x0B28);
                              }
                           } else {
                              return (c >= 0x0B2A && c <= 0x0B30);
                           }
                        } else {
                           if(c < 0x0B3C){
                              if(c < 0x0B35){
                                 return (c >= 0x0B32 && c <= 0x0B33);
                              } else {
                                 return (c >= 0x0B35 && c <= 0x0B39);
                              }
                           } else {
                              return (c >= 0x0B3C && c <= 0x0B44);
                           }
                        }
                     } else {
                        if(c < 0x0B5C){
                           if(c < 0x0B55){
                              if(c < 0x0B4B){
                                 return (c >= 0x0B47 && c <= 0x0B48);
                              } else {
                                 return (c >= 0x0B4B && c <= 0x0B4D);
                              }
                           } else {
                              return (c >= 0x0B55 && c <= 0x0B57);
                           }
                        } else {
                           if(c < 0x0B5F){
                              return (c >= 0x0B5C && c <= 0x0B5D);
                           } else {
                              return (c >= 0x0B5F && c <= 0x0B63);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x0BBE){
                     if(c < 0x0B99){
                        if(c < 0x0B85){
                           if(c < 0x0B82){
                              if(c < 0x0B71){
                                 return (c >= 0x0B66 && c <= 0x0B6F);
                              } else {
                                 return (c >= 0x0B71 && c <= 0x0B71);
                              }
                           } else {
                              return (c >= 0x0B82 && c <= 0x0B83);
                           }
                        } else {
                           if(c < 0x0B92){
                              if(c < 0x0B8E){
                                 return (c >= 0x0B85 && c <= 0x0B8A);
                              } else {
                                 return (c >= 0x0B8E && c <= 0x0B90);
                              }
                           } else {
                              return (c >= 0x0B92 && c <= 0x0B95);
                           }
                        }
                     } else {
                        if(c < 0x0BA3){
                           if(c < 0x0B9E){
                              if(c < 0x0B9C){
                                 return (c >= 0x0B99 && c <= 0x0B9A);
                              } else {
                                 return (c >= 0x0B9C && c <= 0x0B9C);
                              }
                           } else {
                              return (c >= 0x0B9E && c <= 0x0B9F);
                           }
                        } else {
                           if(c < 0x0BAE){
                              if(c < 0x0BA8){
                                 return (c >= 0x0BA3 && c <= 0x0BA4);
                              } else {
                                 return (c >= 0x0BA8 && c <= 0x0BAA);
                              }
                           } else {
                              return (c >= 0x0BAE && c <= 0x0BB9);
                           }
                        }
                     }
                  } else {
                     if(c < 0x0C00){
                        if(c < 0x0BD0){
                           if(c < 0x0BCA){
                              if(c < 0x0BC6){
                                 return (c >= 0x0BBE && c <= 0x0BC2);
                              } else {
                                 return (c >= 0x0BC6 && c <= 0x0BC8);
                              }
                           } else {
                              return (c >= 0x0BCA && c <= 0x0BCD);
                           }
                        } else {
                           if(c < 0x0BE6){
                              if(c < 0x0BD7){
                                 return (c >= 0x0BD0 && c <= 0x0BD0);
                              } else {
                                 return (c >= 0x0BD7 && c <= 0x0BD7);
                              }
                           } else {
                              return (c >= 0x0BE6 && c <= 0x0BEF);
                           }
                        }
                     } else {
                        if(c < 0x0C2A){
                           if(c < 0x0C12){
                              if(c < 0x0C0E){
                                 return (c >= 0x0C00 && c <= 0x0C0C);
                              } else {
                                 return (c >= 0x0C0E && c <= 0x0C10);
                              }
                           } else {
                              return (c >= 0x0C12 && c <= 0x0C28);
                           }
                        } else {
                           if(c < 0x0C3D){
                              return (c >= 0x0C2A && c <= 0x0C39);
                           } else {
                              return (c >= 0x0C3D && c <= 0x0C44);
                           }
                        }
                     }
                  }
               }
            } else {
               if(c < 0x0D46){
                  if(c < 0x0CBC){
                     if(c < 0x0C80){
                        if(c < 0x0C58){
                           if(c < 0x0C55){
                              if(c < 0x0C4A){
                                 return (c >= 0x0C46 && c <= 0x0C48);
                              } else {
                                 return (c >= 0x0C4A && c <= 0x0C4D);
                              }
                           } else {
                              return (c >= 0x0C55 && c <= 0x0C56);
                           }
                        } else {
                           if(c < 0x0C66){
                              if(c < 0x0C60){
                                 return (c >= 0x0C58 && c <= 0x0C5A);
                              } else {
                                 return (c >= 0x0C60 && c <= 0x0C63);
                              }
                           } else {
                              return (c >= 0x0C66 && c <= 0x0C6F);
                           }
                        }
                     } else {
                        if(c < 0x0C92){
                           if(c < 0x0C8E){
                              if(c < 0x0C85){
                                 return (c >= 0x0C80 && c <= 0x0C83);
                              } else {
                                 return (c >= 0x0C85 && c <= 0x0C8C);
                              }
                           } else {
                              return (c >= 0x0C8E && c <= 0x0C90);
                           }
                        } else {
                           if(c < 0x0CB5){
                              if(c < 0x0CAA){
                                 return (c >= 0x0C92 && c <= 0x0CA8);
                              } else {
                                 return (c >= 0x0CAA && c <= 0x0CB3);
                              }
                           } else {
                              return (c >= 0x0CB5 && c <= 0x0CB9);
                           }
                        }
                     }
                  } else {
                     if(c < 0x0CE6){
                        if(c < 0x0CD5){
                           if(c < 0x0CCA){
                              if(c < 0x0CC6){
                                 return (c >= 0x0CBC && c <= 0x0CC4);
                              } else {
                                 return (c >= 0x0CC6 && c <= 0x0CC8);
                              }
                           } else {
                              return (c >= 0x0CCA && c <= 0x0CCD);
                           }
                        } else {
                           if(c < 0x0CE0){
                              if(c < 0x0CDE){
                                 return (c >= 0x0CD5 && c <= 0x0CD6);
                              } else {
                                 return (c >= 0x0CDE && c <= 0x0CDE);
                              }
                           } else {
                              return (c >= 0x0CE0 && c <= 0x0CE3);
                           }
                        }
                     } else {
                        if(c < 0x0D0E){
                           if(c < 0x0D00){
                              if(c < 0x0CF1){
                                 return (c >= 0x0CE6 && c <= 0x0CEF);
                              } else {
                                 return (c >= 0x0CF1 && c <= 0x0CF2);
                              }
                           } else {
                              return (c >= 0x0D00 && c <= 0x0D0C);
                           }
                        } else {
                           if(c < 0x0D12){
                              return (c >= 0x0D0E && c <= 0x0D10);
                           } else {
                              return (c >= 0x0D12 && c <= 0x0D44);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x0DC0){
                     if(c < 0x0D81){
                        if(c < 0x0D5F){
                           if(c < 0x0D54){
                              if(c < 0x0D4A){
                                 return (c >= 0x0D46 && c <= 0x0D48);
                              } else {
                                 return (c >= 0x0D4A && c <= 0x0D4E);
                              }
                           } else {
                              return (c >= 0x0D54 && c <= 0x0D57);
                           }
                        } else {
                           if(c < 0x0D7A){
                              if(c < 0x0D66){
                                 return (c >= 0x0D5F && c <= 0x0D63);
                              } else {
                                 return (c >= 0x0D66 && c <= 0x0D6F);
                              }
                           } else {
                              return (c >= 0x0D7A && c <= 0x0D7F);
                           }
                        }
                     } else {
                        if(c < 0x0DB3){
                           if(c < 0x0D9A){
                              if(c < 0x0D85){
                                 return (c >= 0x0D81 && c <= 0x0D83);
                              } else {
                                 return (c >= 0x0D85 && c <= 0x0D96);
                              }
                           } else {
                              return (c >= 0x0D9A && c <= 0x0DB1);
                           }
                        } else {
                           if(c < 0x0DBD){
                              return (c >= 0x0DB3 && c <= 0x0DBB);
                           } else {
                              return (c >= 0x0DBD && c <= 0x0DBD);
                           }
                        }
                     }
                  } else {
                     if(c < 0x0DF2){
                        if(c < 0x0DD6){
                           if(c < 0x0DCF){
                              if(c < 0x0DCA){
                                 return (c >= 0x0DC0 && c <= 0x0DC6);
                              } else {
                                 return (c >= 0x0DCA && c <= 0x0DCA);
                              }
                           } else {
                              return (c >= 0x0DCF && c <= 0x0DD4);
                           }
                        } else {
                           if(c < 0x0DE6){
                              if(c < 0x0DD8){
                                 return (c >= 0x0DD6 && c <= 0x0DD6);
                              } else {
                                 return (c >= 0x0DD8 && c <= 0x0DDF);
                              }
                           } else {
                              return (c >= 0x0DE6 && c <= 0x0DEF);
                           }
                        }
                     } else {
                        if(c < 0x0E50){
                           if(c < 0x0E40){
                              if(c < 0x0E01){
                                 return (c >= 0x0DF2 && c <= 0x0DF3);
                              } else {
                                 return (c >= 0x0E01 && c <= 0x0E3A);
                              }
                           } else {
                              return (c >= 0x0E40 && c <= 0x0E4E);
                           }
                        } else {
                           if(c < 0x0E81){
                              return (c >= 0x0E50 && c <= 0x0E59);
                           } else {
                              return (c >= 0x0E81 && c <= 0x0E82);
                           }
                        }
                     }
                  }
               }
            }
         }
      } else {
         if(c < 0x1C40){
            if(c < 0x1380){
               if(c < 0x1050){
                  if(c < 0x0F20){
                     if(c < 0x0EC6){
                        if(c < 0x0EA5){
                           if(c < 0x0E8C){
                              if(c < 0x0E86){
                                 return (c >= 0x0E84 && c <= 0x0E84);
                              } else {
                                 return (c >= 0x0E86 && c <= 0x0E8A);
                              }
                           } else {
                              return (c >= 0x0E8C && c <= 0x0EA3);
                           }
                        } else {
                           if(c < 0x0EC0){
                              if(c < 0x0EA7){
                                 return (c >= 0x0EA5 && c <= 0x0EA5);
                              } else {
                                 return (c >= 0x0EA7 && c <= 0x0EBD);
                              }
                           } else {
                              return (c >= 0x0EC0 && c <= 0x0EC4);
                           }
                        }
                     } else {
                        if(c < 0x0EDC){
                           if(c < 0x0ED0){
                              if(c < 0x0EC8){
                                 return (c >= 0x0EC6 && c <= 0x0EC6);
                              } else {
                                 return (c >= 0x0EC8 && c <= 0x0ECD);
                              }
                           } else {
                              return (c >= 0x0ED0 && c <= 0x0ED9);
                           }
                        } else {
                           if(c < 0x0F18){
                              if(c < 0x0F00){
                                 return (c >= 0x0EDC && c <= 0x0EDF);
                              } else {
                                 return (c >= 0x0F00 && c <= 0x0F00);
                              }
                           } else {
                              return (c >= 0x0F18 && c <= 0x0F19);
                           }
                        }
                     }
                  } else {
                     if(c < 0x0F71){
                        if(c < 0x0F39){
                           if(c < 0x0F37){
                              if(c < 0x0F35){
                                 return (c >= 0x0F20 && c <= 0x0F29);
                              } else {
                                 return (c >= 0x0F35 && c <= 0x0F35);
                              }
                           } else {
                              return (c >= 0x0F37 && c <= 0x0F37);
                           }
                        } else {
                           if(c < 0x0F49){
                              if(c < 0x0F3E){
                                 return (c >= 0x0F39 && c <= 0x0F39);
                              } else {
                                 return (c >= 0x0F3E && c <= 0x0F47);
                              }
                           } else {
                              return (c >= 0x0F49 && c <= 0x0F6C);
                           }
                        }
                     } else {
                        if(c < 0x0FC6){
                           if(c < 0x0F99){
                              if(c < 0x0F86){
                                 return (c >= 0x0F71 && c <= 0x0F84);
                              } else {
                                 return (c >= 0x0F86 && c <= 0x0F97);
                              }
                           } else {
                              return (c >= 0x0F99 && c <= 0x0FBC);
                           }
                        } else {
                           if(c < 0x1000){
                              return (c >= 0x0FC6 && c <= 0x0FC6);
                           } else {
                              return (c >= 0x1000 && c <= 0x1049);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x1290){
                     if(c < 0x124A){
                        if(c < 0x10CD){
                           if(c < 0x10C7){
                              if(c < 0x10A0){
                                 return (c >= 0x1050 && c <= 0x109D);
                              } else {
                                 return (c >= 0x10A0 && c <= 0x10C5);
                              }
                           } else {
                              return (c >= 0x10C7 && c <= 0x10C7);
                           }
                        } else {
                           if(c < 0x10FC){
                              if(c < 0x10D0){
                                 return (c >= 0x10CD && c <= 0x10CD);
                              } else {
                                 return (c >= 0x10D0 && c <= 0x10FA);
                              }
                           } else {
                              return (c >= 0x10FC && c <= 0x1248);
                           }
                        }
                     } else {
                        if(c < 0x125A){
                           if(c < 0x1258){
                              if(c < 0x1250){
                                 return (c >= 0x124A && c <= 0x124D);
                              } else {
                                 return (c >= 0x1250 && c <= 0x1256);
                              }
                           } else {
                              return (c >= 0x1258 && c <= 0x1258);
                           }
                        } else {
                           if(c < 0x128A){
                              if(c < 0x1260){
                                 return (c >= 0x125A && c <= 0x125D);
                              } else {
                                 return (c >= 0x1260 && c <= 0x1288);
                              }
                           } else {
                              return (c >= 0x128A && c <= 0x128D);
                           }
                        }
                     }
                  } else {
                     if(c < 0x12D8){
                        if(c < 0x12C0){
                           if(c < 0x12B8){
                              if(c < 0x12B2){
                                 return (c >= 0x1290 && c <= 0x12B0);
                              } else {
                                 return (c >= 0x12B2 && c <= 0x12B5);
                              }
                           } else {
                              return (c >= 0x12B8 && c <= 0x12BE);
                           }
                        } else {
                           if(c < 0x12C8){
                              if(c < 0x12C2){
                                 return (c >= 0x12C0 && c <= 0x12C0);
                              } else {
                                 return (c >= 0x12C2 && c <= 0x12C5);
                              }
                           } else {
                              return (c >= 0x12C8 && c <= 0x12D6);
                           }
                        }
                     } else {
                        if(c < 0x135D){
                           if(c < 0x1318){
                              if(c < 0x1312){
                                 return (c >= 0x12D8 && c <= 0x1310);
                              } else {
                                 return (c >= 0x1312 && c <= 0x1315);
                              }
                           } else {
                              return (c >= 0x1318 && c <= 0x135A);
                           }
                        } else {
                           if(c < 0x1369){
                              return (c >= 0x135D && c <= 0x135F);
                           } else {
                              return (c >= 0x1369 && c <= 0x1371);
                           }
                        }
                     }
                  }
               }
            } else {
               if(c < 0x18B0){
                  if(c < 0x1760){
                     if(c < 0x16A0){
                        if(c < 0x1401){
                           if(c < 0x13F8){
                              if(c < 0x13A0){
                                 return (c >= 0x1380 && c <= 0x138F);
                              } else {
                                 return (c >= 0x13A0 && c <= 0x13F5);
                              }
                           } else {
                              return (c >= 0x13F8 && c <= 0x13FD);
                           }
                        } else {
                           if(c < 0x1681){
                              if(c < 0x166F){
                                 return (c >= 0x1401 && c <= 0x166C);
                              } else {
                                 return (c >= 0x166F && c <= 0x167F);
                              }
                           } else {
                              return (c >= 0x1681 && c <= 0x169A);
                           }
                        }
                     } else {
                        if(c < 0x170E){
                           if(c < 0x1700){
                              if(c < 0x16EE){
                                 return (c >= 0x16A0 && c <= 0x16EA);
                              } else {
                                 return (c >= 0x16EE && c <= 0x16F8);
                              }
                           } else {
                              return (c >= 0x1700 && c <= 0x170C);
                           }
                        } else {
                           if(c < 0x1740){
                              if(c < 0x1720){
                                 return (c >= 0x170E && c <= 0x1714);
                              } else {
                                 return (c >= 0x1720 && c <= 0x1734);
                              }
                           } else {
                              return (c >= 0x1740 && c <= 0x1753);
                           }
                        }
                     }
                  } else {
                     if(c < 0x17E0){
                        if(c < 0x1780){
                           if(c < 0x1772){
                              if(c < 0x176E){
                                 return (c >= 0x1760 && c <= 0x176C);
                              } else {
                                 return (c >= 0x176E && c <= 0x1770);
                              }
                           } else {
                              return (c >= 0x1772 && c <= 0x1773);
                           }
                        } else {
                           if(c < 0x17DC){
                              if(c < 0x17D7){
                                 return (c >= 0x1780 && c <= 0x17D3);
                              } else {
                                 return (c >= 0x17D7 && c <= 0x17D7);
                              }
                           } else {
                              return (c >= 0x17DC && c <= 0x17DD);
                           }
                        }
                     } else {
                        if(c < 0x1820){
                           if(c < 0x1810){
                              if(c < 0x180B){
                                 return (c >= 0x17E0 && c <= 0x17E9);
                              } else {
                                 return (c >= 0x180B && c <= 0x180D);
                              }
                           } else {
                              return (c >= 0x1810 && c <= 0x1819);
                           }
                        } else {
                           if(c < 0x1880){
                              return (c >= 0x1820 && c <= 0x1878);
                           } else {
                              return (c >= 0x1880 && c <= 0x18AA);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x1A60){
                     if(c < 0x1980){
                        if(c < 0x1930){
                           if(c < 0x1920){
                              if(c < 0x1900){
                                 return (c >= 0x18B0 && c <= 0x18F5);
                              } else {
                                 return (c >= 0x1900 && c <= 0x191E);
                              }
                           } else {
                              return (c >= 0x1920 && c <= 0x192B);
                           }
                        } else {
                           if(c < 0x1970){
                              if(c < 0x1946){
                                 return (c >= 0x1930 && c <= 0x193B);
                              } else {
                                 return (c >= 0x1946 && c <= 0x196D);
                              }
                           } else {
                              return (c >= 0x1970 && c <= 0x1974);
                           }
                        }
                     } else {
                        if(c < 0x1A00){
                           if(c < 0x19D0){
                              if(c < 0x19B0){
                                 return (c >= 0x1980 && c <= 0x19AB);
                              } else {
                                 return (c >= 0x19B0 && c <= 0x19C9);
                              }
                           } else {
                              return (c >= 0x19D0 && c <= 0x19DA);
                           }
                        } else {
                           if(c < 0x1A20){
                              return (c >= 0x1A00 && c <= 0x1A1B);
                           } else {
                              return (c >= 0x1A20 && c <= 0x1A5E);
                           }
                        }
                     }
                  } else {
                     if(c < 0x1B00){
                        if(c < 0x1AA7){
                           if(c < 0x1A90){
                              if(c < 0x1A7F){
                                 return (c >= 0x1A60 && c <= 0x1A7C);
                              } else {
                                 return (c >= 0x1A7F && c <= 0x1A89);
                              }
                           } else {
                              return (c >= 0x1A90 && c <= 0x1A99);
                           }
                        } else {
                           if(c < 0x1ABF){
                              if(c < 0x1AB0){
                                 return (c >= 0x1AA7 && c <= 0x1AA7);
                              } else {
                                 return (c >= 0x1AB0 && c <= 0x1ABD);
                              }
                           } else {
                              return (c >= 0x1ABF && c <= 0x1AC0);
                           }
                        }
                     } else {
                        if(c < 0x1B80){
                           if(c < 0x1B6B){
                              if(c < 0x1B50){
                                 return (c >= 0x1B00 && c <= 0x1B4B);
                              } else {
                                 return (c >= 0x1B50 && c <= 0x1B59);
                              }
                           } else {
                              return (c >= 0x1B6B && c <= 0x1B73);
                           }
                        } else {
                           if(c < 0x1C00){
                              return (c >= 0x1B80 && c <= 0x1BF3);
                           } else {
                              return (c >= 0x1C00 && c <= 0x1C37);
                           }
                        }
                     }
                  }
               }
            }
         } else {
            if(c < 0x214E){
               if(c < 0x1FD6){
                  if(c < 0x1F50){
                     if(c < 0x1CD4){
                        if(c < 0x1C90){
                           if(c < 0x1C80){
                              if(c < 0x1C4D){
                                 return (c >= 0x1C40 && c <= 0x1C49);
                              } else {
                                 return (c >= 0x1C4D && c <= 0x1C7D);
                              }
                           } else {
                              return (c >= 0x1C80 && c <= 0x1C88);
                           }
                        } else {
                           if(c < 0x1CD0){
                              if(c < 0x1CBD){
                                 return (c >= 0x1C90 && c <= 0x1CBA);
                              } else {
                                 return (c >= 0x1CBD && c <= 0x1CBF);
                              }
                           } else {
                              return (c >= 0x1CD0 && c <= 0x1CD2);
                           }
                        }
                     } else {
                        if(c < 0x1F18){
                           if(c < 0x1DFB){
                              if(c < 0x1D00){
                                 return (c >= 0x1CD4 && c <= 0x1CFA);
                              } else {
                                 return (c >= 0x1D00 && c <= 0x1DF9);
                              }
                           } else {
                              return (c >= 0x1DFB && c <= 0x1F15);
                           }
                        } else {
                           if(c < 0x1F48){
                              if(c < 0x1F20){
                                 return (c >= 0x1F18 && c <= 0x1F1D);
                              } else {
                                 return (c >= 0x1F20 && c <= 0x1F45);
                              }
                           } else {
                              return (c >= 0x1F48 && c <= 0x1F4D);
                           }
                        }
                     }
                  } else {
                     if(c < 0x1FB6){
                        if(c < 0x1F5D){
                           if(c < 0x1F5B){
                              if(c < 0x1F59){
                                 return (c >= 0x1F50 && c <= 0x1F57);
                              } else {
                                 return (c >= 0x1F59 && c <= 0x1F59);
                              }
                           } else {
                              return (c >= 0x1F5B && c <= 0x1F5B);
                           }
                        } else {
                           if(c < 0x1F80){
                              if(c < 0x1F5F){
                                 return (c >= 0x1F5D && c <= 0x1F5D);
                              } else {
                                 return (c >= 0x1F5F && c <= 0x1F7D);
                              }
                           } else {
                              return (c >= 0x1F80 && c <= 0x1FB4);
                           }
                        }
                     } else {
                        if(c < 0x1FC6){
                           if(c < 0x1FC2){
                              if(c < 0x1FBE){
                                 return (c >= 0x1FB6 && c <= 0x1FBC);
                              } else {
                                 return (c >= 0x1FBE && c <= 0x1FBE);
                              }
                           } else {
                              return (c >= 0x1FC2 && c <= 0x1FC4);
                           }
                        } else {
                           if(c < 0x1FD0){
                              return (c >= 0x1FC6 && c <= 0x1FCC);
                           } else {
                              return (c >= 0x1FD0 && c <= 0x1FD3);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x2102){
                     if(c < 0x2071){
                        if(c < 0x1FF6){
                           if(c < 0x1FF2){
                              if(c < 0x1FE0){
                                 return (c >= 0x1FD6 && c <= 0x1FDB);
                              } else {
                                 return (c >= 0x1FE0 && c <= 0x1FEC);
                              }
                           } else {
                              return (c >= 0x1FF2 && c <= 0x1FF4);
                           }
                        } else {
                           if(c < 0x2054){
                              if(c < 0x203F){
                                 return (c >= 0x1FF6 && c <= 0x1FFC);
                              } else {
                                 return (c >= 0x203F && c <= 0x2040);
                              }
                           } else {
                              return (c >= 0x2054 && c <= 0x2054);
                           }
                        }
                     } else {
                        if(c < 0x20D0){
                           if(c < 0x2090){
                              if(c < 0x207F){
                                 return (c >= 0x2071 && c <= 0x2071);
                              } else {
                                 return (c >= 0x207F && c <= 0x207F);
                              }
                           } else {
                              return (c >= 0x2090 && c <= 0x209C);
                           }
                        } else {
                           if(c < 0x20E5){
                              if(c < 0x20E1){
                                 return (c >= 0x20D0 && c <= 0x20DC);
                              } else {
                                 return (c >= 0x20E1 && c <= 0x20E1);
                              }
                           } else {
                              return (c >= 0x20E5 && c <= 0x20F0);
                           }
                        }
                     }
                  } else {
                     if(c < 0x2126){
                        if(c < 0x2115){
                           if(c < 0x210A){
                              if(c < 0x2107){
                                 return (c >= 0x2102 && c <= 0x2102);
                              } else {
                                 return (c >= 0x2107 && c <= 0x2107);
                              }
                           } else {
                              return (c >= 0x210A && c <= 0x2113);
                           }
                        } else {
                           if(c < 0x2124){
                              if(c < 0x2118){
                                 return (c >= 0x2115 && c <= 0x2115);
                              } else {
                                 return (c >= 0x2118 && c <= 0x211D);
                              }
                           } else {
                              return (c >= 0x2124 && c <= 0x2124);
                           }
                        }
                     } else {
                        if(c < 0x213C){
                           if(c < 0x212A){
                              if(c < 0x2128){
                                 return (c >= 0x2126 && c <= 0x2126);
                              } else {
                                 return (c >= 0x2128 && c <= 0x2128);
                              }
                           } else {
                              return (c >= 0x212A && c <= 0x2139);
                           }
                        } else {
                           if(c < 0x2145){
                              return (c >= 0x213C && c <= 0x213F);
                           } else {
                              return (c >= 0x2145 && c <= 0x2149);
                           }
                        }
                     }
                  }
               }
            } else {
               if(c < 0x3031){
                  if(c < 0x2DA0){
                     if(c < 0x2D00){
                        if(c < 0x2C30){
                           if(c < 0x2C00){
                              if(c < 0x2160){
                                 return (c >= 0x214E && c <= 0x214E);
                              } else {
                                 return (c >= 0x2160 && c <= 0x2188);
                              }
                           } else {
                              return (c >= 0x2C00 && c <= 0x2C2E);
                           }
                        } else {
                           if(c < 0x2CEB){
                              if(c < 0x2C60){
                                 return (c >= 0x2C30 && c <= 0x2C5E);
                              } else {
                                 return (c >= 0x2C60 && c <= 0x2CE4);
                              }
                           } else {
                              return (c >= 0x2CEB && c <= 0x2CF3);
                           }
                        }
                     } else {
                        if(c < 0x2D30){
                           if(c < 0x2D2D){
                              if(c < 0x2D27){
                                 return (c >= 0x2D00 && c <= 0x2D25);
                              } else {
                                 return (c >= 0x2D27 && c <= 0x2D27);
                              }
                           } else {
                              return (c >= 0x2D2D && c <= 0x2D2D);
                           }
                        } else {
                           if(c < 0x2D7F){
                              if(c < 0x2D6F){
                                 return (c >= 0x2D30 && c <= 0x2D67);
                              } else {
                                 return (c >= 0x2D6F && c <= 0x2D6F);
                              }
                           } else {
                              return (c >= 0x2D7F && c <= 0x2D96);
                           }
                        }
                     }
                  } else {
                     if(c < 0x2DD0){
                        if(c < 0x2DB8){
                           if(c < 0x2DB0){
                              if(c < 0x2DA8){
                                 return (c >= 0x2DA0 && c <= 0x2DA6);
                              } else {
                                 return (c >= 0x2DA8 && c <= 0x2DAE);
                              }
                           } else {
                              return (c >= 0x2DB0 && c <= 0x2DB6);
                           }
                        } else {
                           if(c < 0x2DC8){
                              if(c < 0x2DC0){
                                 return (c >= 0x2DB8 && c <= 0x2DBE);
                              } else {
                                 return (c >= 0x2DC0 && c <= 0x2DC6);
                              }
                           } else {
                              return (c >= 0x2DC8 && c <= 0x2DCE);
                           }
                        }
                     } else {
                        if(c < 0x3005){
                           if(c < 0x2DE0){
                              if(c < 0x2DD8){
                                 return (c >= 0x2DD0 && c <= 0x2DD6);
                              } else {
                                 return (c >= 0x2DD8 && c <= 0x2DDE);
                              }
                           } else {
                              return (c >= 0x2DE0 && c <= 0x2DFF);
                           }
                        } else {
                           if(c < 0x3021){
                              return (c >= 0x3005 && c <= 0x3007);
                           } else {
                              return (c >= 0x3021 && c <= 0x302F);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x4E00){
                     if(c < 0x3105){
                        if(c < 0x3099){
                           if(c < 0x3041){
                              if(c < 0x3038){
                                 return (c >= 0x3031 && c <= 0x3035);
                              } else {
                                 return (c >= 0x3038 && c <= 0x303C);
                              }
                           } else {
                              return (c >= 0x3041 && c <= 0x3096);
                           }
                        } else {
                           if(c < 0x30FC){
                              if(c < 0x30A1){
                                 return (c >= 0x3099 && c <= 0x309F);
                              } else {
                                 return (c >= 0x30A1 && c <= 0x30FA);
                              }
                           } else {
                              return (c >= 0x30FC && c <= 0x30FF);
                           }
                        }
                     } else {
                        if(c < 0x31F0){
                           if(c < 0x31A0){
                              if(c < 0x3131){
                                 return (c >= 0x3105 && c <= 0x312F);
                              } else {
                                 return (c >= 0x3131 && c <= 0x318E);
                              }
                           } else {
                              return (c >= 0x31A0 && c <= 0x31BF);
                           }
                        } else {
                           if(c < 0x3400){
                              return (c >= 0x31F0 && c <= 0x31FF);
                           } else {
                              return (c >= 0x3400 && c <= 0x4DBF);
                           }
                        }
                     }
                  } else {
                     if(c < 0xA674){
                        if(c < 0xA500){
                           if(c < 0xA4D0){
                              if(c < 0xA000){
                                 return (c >= 0x4E00 && c <= 0x9FFC);
                              } else {
                                 return (c >= 0xA000 && c <= 0xA48C);
                              }
                           } else {
                              return (c >= 0xA4D0 && c <= 0xA4FD);
                           }
                        } else {
                           if(c < 0xA640){
                              if(c < 0xA610){
                                 return (c >= 0xA500 && c <= 0xA60C);
                              } else {
                                 return (c >= 0xA610 && c <= 0xA62B);
                              }
                           } else {
                              return (c >= 0xA640 && c <= 0xA66F);
                           }
                        }
                     } else {
                        if(c < 0xA722){
                           if(c < 0xA717){
                              if(c < 0xA67F){
                                 return (c >= 0xA674 && c <= 0xA67D);
                              } else {
                                 return (c >= 0xA67F && c <= 0xA6F1);
                              }
                           } else {
                              return (c >= 0xA717 && c <= 0xA71F);
                           }
                        } else {
                           if(c < 0xA78B){
                              return (c >= 0xA722 && c <= 0xA788);
                           } else {
                              return (c >= 0xA78B && c <= 0xA7BF);
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   } else {
      if(c < 0x011600){
         if(c < 0x010760){
            if(c < 0xFBD3){
               if(c < 0xAB09){
                  if(c < 0xA9CF){
                     if(c < 0xA8E0){
                        if(c < 0xA840){
                           if(c < 0xA82C){
                              if(c < 0xA7F5){
                                 return (c >= 0xA7C2 && c <= 0xA7CA);
                              } else {
                                 return (c >= 0xA7F5 && c <= 0xA827);
                              }
                           } else {
                              return (c >= 0xA82C && c <= 0xA82C);
                           }
                        } else {
                           if(c < 0xA8D0){
                              if(c < 0xA880){
                                 return (c >= 0xA840 && c <= 0xA873);
                              } else {
                                 return (c >= 0xA880 && c <= 0xA8C5);
                              }
                           } else {
                              return (c >= 0xA8D0 && c <= 0xA8D9);
                           }
                        }
                     } else {
                        if(c < 0xA930){
                           if(c < 0xA8FD){
                              if(c < 0xA8FB){
                                 return (c >= 0xA8E0 && c <= 0xA8F7);
                              } else {
                                 return (c >= 0xA8FB && c <= 0xA8FB);
                              }
                           } else {
                              return (c >= 0xA8FD && c <= 0xA92D);
                           }
                        } else {
                           if(c < 0xA980){
                              if(c < 0xA960){
                                 return (c >= 0xA930 && c <= 0xA953);
                              } else {
                                 return (c >= 0xA960 && c <= 0xA97C);
                              }
                           } else {
                              return (c >= 0xA980 && c <= 0xA9C0);
                           }
                        }
                     }
                  } else {
                     if(c < 0xAA7A){
                        if(c < 0xAA40){
                           if(c < 0xAA00){
                              if(c < 0xA9E0){
                                 return (c >= 0xA9CF && c <= 0xA9D9);
                              } else {
                                 return (c >= 0xA9E0 && c <= 0xA9FE);
                              }
                           } else {
                              return (c >= 0xAA00 && c <= 0xAA36);
                           }
                        } else {
                           if(c < 0xAA60){
                              if(c < 0xAA50){
                                 return (c >= 0xAA40 && c <= 0xAA4D);
                              } else {
                                 return (c >= 0xAA50 && c <= 0xAA59);
                              }
                           } else {
                              return (c >= 0xAA60 && c <= 0xAA76);
                           }
                        }
                     } else {
                        if(c < 0xAAF2){
                           if(c < 0xAAE0){
                              if(c < 0xAADB){
                                 return (c >= 0xAA7A && c <= 0xAAC2);
                              } else {
                                 return (c >= 0xAADB && c <= 0xAADD);
                              }
                           } else {
                              return (c >= 0xAAE0 && c <= 0xAAEF);
                           }
                        } else {
                           if(c < 0xAB01){
                              return (c >= 0xAAF2 && c <= 0xAAF6);
                           } else {
                              return (c >= 0xAB01 && c <= 0xAB06);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0xF900){
                     if(c < 0xAB70){
                        if(c < 0xAB28){
                           if(c < 0xAB20){
                              if(c < 0xAB11){
                                 return (c >= 0xAB09 && c <= 0xAB0E);
                              } else {
                                 return (c >= 0xAB11 && c <= 0xAB16);
                              }
                           } else {
                              return (c >= 0xAB20 && c <= 0xAB26);
                           }
                        } else {
                           if(c < 0xAB5C){
                              if(c < 0xAB30){
                                 return (c >= 0xAB28 && c <= 0xAB2E);
                              } else {
                                 return (c >= 0xAB30 && c <= 0xAB5A);
                              }
                           } else {
                              return (c >= 0xAB5C && c <= 0xAB69);
                           }
                        }
                     } else {
                        if(c < 0xAC00){
                           if(c < 0xABF0){
                              if(c < 0xABEC){
                                 return (c >= 0xAB70 && c <= 0xABEA);
                              } else {
                                 return (c >= 0xABEC && c <= 0xABED);
                              }
                           } else {
                              return (c >= 0xABF0 && c <= 0xABF9);
                           }
                        } else {
                           if(c < 0xD7CB){
                              if(c < 0xD7B0){
                                 return (c >= 0xAC00 && c <= 0xD7A3);
                              } else {
                                 return (c >= 0xD7B0 && c <= 0xD7C6);
                              }
                           } else {
                              return (c >= 0xD7CB && c <= 0xD7FB);
                           }
                        }
                     }
                  } else {
                     if(c < 0xFB38){
                        if(c < 0xFB13){
                           if(c < 0xFB00){
                              if(c < 0xFA70){
                                 return (c >= 0xF900 && c <= 0xFA6D);
                              } else {
                                 return (c >= 0xFA70 && c <= 0xFAD9);
                              }
                           } else {
                              return (c >= 0xFB00 && c <= 0xFB06);
                           }
                        } else {
                           if(c < 0xFB2A){
                              if(c < 0xFB1D){
                                 return (c >= 0xFB13 && c <= 0xFB17);
                              } else {
                                 return (c >= 0xFB1D && c <= 0xFB28);
                              }
                           } else {
                              return (c >= 0xFB2A && c <= 0xFB36);
                           }
                        }
                     } else {
                        if(c < 0xFB43){
                           if(c < 0xFB40){
                              if(c < 0xFB3E){
                                 return (c >= 0xFB38 && c <= 0xFB3C);
                              } else {
                                 return (c >= 0xFB3E && c <= 0xFB3E);
                              }
                           } else {
                              return (c >= 0xFB40 && c <= 0xFB41);
                           }
                        } else {
                           if(c < 0xFB46){
                              return (c >= 0xFB43 && c <= 0xFB44);
                           } else {
                              return (c >= 0xFB46 && c <= 0xFBB1);
                           }
                        }
                     }
                  }
               }
            } else {
               if(c < 0x01003F){
                  if(c < 0xFF3F){
                     if(c < 0xFE33){
                        if(c < 0xFDF0){
                           if(c < 0xFD92){
                              if(c < 0xFD50){
                                 return (c >= 0xFBD3 && c <= 0xFD3D);
                              } else {
                                 return (c >= 0xFD50 && c <= 0xFD8F);
                              }
                           } else {
                              return (c >= 0xFD92 && c <= 0xFDC7);
                           }
                        } else {
                           if(c < 0xFE20){
                              if(c < 0xFE00){
                                 return (c >= 0xFDF0 && c <= 0xFDFB);
                              } else {
                                 return (c >= 0xFE00 && c <= 0xFE0F);
                              }
                           } else {
                              return (c >= 0xFE20 && c <= 0xFE2F);
                           }
                        }
                     } else {
                        if(c < 0xFE76){
                           if(c < 0xFE70){
                              if(c < 0xFE4D){
                                 return (c >= 0xFE33 && c <= 0xFE34);
                              } else {
                                 return (c >= 0xFE4D && c <= 0xFE4F);
                              }
                           } else {
                              return (c >= 0xFE70 && c <= 0xFE74);
                           }
                        } else {
                           if(c < 0xFF21){
                              if(c < 0xFF10){
                                 return (c >= 0xFE76 && c <= 0xFEFC);
                              } else {
                                 return (c >= 0xFF10 && c <= 0xFF19);
                              }
                           } else {
                              return (c >= 0xFF21 && c <= 0xFF3A);
                           }
                        }
                     }
                  } else {
                     if(c < 0xFFDA){
                        if(c < 0xFFC2){
                           if(c < 0xFF66){
                              if(c < 0xFF41){
                                 return (c >= 0xFF3F && c <= 0xFF3F);
                              } else {
                                 return (c >= 0xFF41 && c <= 0xFF5A);
                              }
                           } else {
                              return (c >= 0xFF66 && c <= 0xFFBE);
                           }
                        } else {
                           if(c < 0xFFD2){
                              if(c < 0xFFCA){
                                 return (c >= 0xFFC2 && c <= 0xFFC7);
                              } else {
                                 return (c >= 0xFFCA && c <= 0xFFCF);
                              }
                           } else {
                              return (c >= 0xFFD2 && c <= 0xFFD7);
                           }
                        }
                     } else {
                        if(c < 0x010028){
                           if(c < 0x01000D){
                              if(c < 0x010000){
                                 return (c >= 0xFFDA && c <= 0xFFDC);
                              } else {
                                 return (c >= 0x010000 && c <= 0x01000B);
                              }
                           } else {
                              return (c >= 0x01000D && c <= 0x010026);
                           }
                        } else {
                           if(c < 0x01003C){
                              return (c >= 0x010028 && c <= 0x01003A);
                           } else {
                              return (c >= 0x01003C && c <= 0x01003D);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x0103A0){
                     if(c < 0x0102A0){
                        if(c < 0x010140){
                           if(c < 0x010080){
                              if(c < 0x010050){
                                 return (c >= 0x01003F && c <= 0x01004D);
                              } else {
                                 return (c >= 0x010050 && c <= 0x01005D);
                              }
                           } else {
                              return (c >= 0x010080 && c <= 0x0100FA);
                           }
                        } else {
                           if(c < 0x010280){
                              if(c < 0x0101FD){
                                 return (c >= 0x010140 && c <= 0x010174);
                              } else {
                                 return (c >= 0x0101FD && c <= 0x0101FD);
                              }
                           } else {
                              return (c >= 0x010280 && c <= 0x01029C);
                           }
                        }
                     } else {
                        if(c < 0x01032D){
                           if(c < 0x010300){
                              if(c < 0x0102E0){
                                 return (c >= 0x0102A0 && c <= 0x0102D0);
                              } else {
                                 return (c >= 0x0102E0 && c <= 0x0102E0);
                              }
                           } else {
                              return (c >= 0x010300 && c <= 0x01031F);
                           }
                        } else {
                           if(c < 0x010380){
                              if(c < 0x010350){
                                 return (c >= 0x01032D && c <= 0x01034A);
                              } else {
                                 return (c >= 0x010350 && c <= 0x01037A);
                              }
                           } else {
                              return (c >= 0x010380 && c <= 0x01039D);
                           }
                        }
                     }
                  } else {
                     if(c < 0x0104D8){
                        if(c < 0x010400){
                           if(c < 0x0103D1){
                              if(c < 0x0103C8){
                                 return (c >= 0x0103A0 && c <= 0x0103C3);
                              } else {
                                 return (c >= 0x0103C8 && c <= 0x0103CF);
                              }
                           } else {
                              return (c >= 0x0103D1 && c <= 0x0103D5);
                           }
                        } else {
                           if(c < 0x0104B0){
                              if(c < 0x0104A0){
                                 return (c >= 0x010400 && c <= 0x01049D);
                              } else {
                                 return (c >= 0x0104A0 && c <= 0x0104A9);
                              }
                           } else {
                              return (c >= 0x0104B0 && c <= 0x0104D3);
                           }
                        }
                     } else {
                        if(c < 0x010600){
                           if(c < 0x010530){
                              if(c < 0x010500){
                                 return (c >= 0x0104D8 && c <= 0x0104FB);
                              } else {
                                 return (c >= 0x010500 && c <= 0x010527);
                              }
                           } else {
                              return (c >= 0x010530 && c <= 0x010563);
                           }
                        } else {
                           if(c < 0x010740){
                              return (c >= 0x010600 && c <= 0x010736);
                           } else {
                              return (c >= 0x010740 && c <= 0x010755);
                           }
                        }
                     }
                  }
               }
            }
         } else {
            if(c < 0x0110D0){
               if(c < 0x010A80){
                  if(c < 0x010920){
                     if(c < 0x01083F){
                        if(c < 0x01080A){
                           if(c < 0x010808){
                              if(c < 0x010800){
                                 return (c >= 0x010760 && c <= 0x010767);
                              } else {
                                 return (c >= 0x010800 && c <= 0x010805);
                              }
                           } else {
                              return (c >= 0x010808 && c <= 0x010808);
                           }
                        } else {
                           if(c < 0x01083C){
                              if(c < 0x010837){
                                 return (c >= 0x01080A && c <= 0x010835);
                              } else {
                                 return (c >= 0x010837 && c <= 0x010838);
                              }
                           } else {
                              return (c >= 0x01083C && c <= 0x01083C);
                           }
                        }
                     } else {
                        if(c < 0x0108E0){
                           if(c < 0x010880){
                              if(c < 0x010860){
                                 return (c >= 0x01083F && c <= 0x010855);
                              } else {
                                 return (c >= 0x010860 && c <= 0x010876);
                              }
                           } else {
                              return (c >= 0x010880 && c <= 0x01089E);
                           }
                        } else {
                           if(c < 0x010900){
                              if(c < 0x0108F4){
                                 return (c >= 0x0108E0 && c <= 0x0108F2);
                              } else {
                                 return (c >= 0x0108F4 && c <= 0x0108F5);
                              }
                           } else {
                              return (c >= 0x010900 && c <= 0x010915);
                           }
                        }
                     }
                  } else {
                     if(c < 0x010A15){
                        if(c < 0x010A00){
                           if(c < 0x0109BE){
                              if(c < 0x010980){
                                 return (c >= 0x010920 && c <= 0x010939);
                              } else {
                                 return (c >= 0x010980 && c <= 0x0109B7);
                              }
                           } else {
                              return (c >= 0x0109BE && c <= 0x0109BF);
                           }
                        } else {
                           if(c < 0x010A0C){
                              if(c < 0x010A05){
                                 return (c >= 0x010A00 && c <= 0x010A03);
                              } else {
                                 return (c >= 0x010A05 && c <= 0x010A06);
                              }
                           } else {
                              return (c >= 0x010A0C && c <= 0x010A13);
                           }
                        }
                     } else {
                        if(c < 0x010A3F){
                           if(c < 0x010A38){
                              if(c < 0x010A19){
                                 return (c >= 0x010A15 && c <= 0x010A17);
                              } else {
                                 return (c >= 0x010A19 && c <= 0x010A35);
                              }
                           } else {
                              return (c >= 0x010A38 && c <= 0x010A3A);
                           }
                        } else {
                           if(c < 0x010A60){
                              return (c >= 0x010A3F && c <= 0x010A3F);
                           } else {
                              return (c >= 0x010A60 && c <= 0x010A7C);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x010E80){
                     if(c < 0x010B80){
                        if(c < 0x010B00){
                           if(c < 0x010AC9){
                              if(c < 0x010AC0){
                                 return (c >= 0x010A80 && c <= 0x010A9C);
                              } else {
                                 return (c >= 0x010AC0 && c <= 0x010AC7);
                              }
                           } else {
                              return (c >= 0x010AC9 && c <= 0x010AE6);
                           }
                        } else {
                           if(c < 0x010B60){
                              if(c < 0x010B40){
                                 return (c >= 0x010B00 && c <= 0x010B35);
                              } else {
                                 return (c >= 0x010B40 && c <= 0x010B55);
                              }
                           } else {
                              return (c >= 0x010B60 && c <= 0x010B72);
                           }
                        }
                     } else {
                        if(c < 0x010CC0){
                           if(c < 0x010C80){
                              if(c < 0x010C00){
                                 return (c >= 0x010B80 && c <= 0x010B91);
                              } else {
                                 return (c >= 0x010C00 && c <= 0x010C48);
                              }
                           } else {
                              return (c >= 0x010C80 && c <= 0x010CB2);
                           }
                        } else {
                           if(c < 0x010D30){
                              if(c < 0x010D00){
                                 return (c >= 0x010CC0 && c <= 0x010CF2);
                              } else {
                                 return (c >= 0x010D00 && c <= 0x010D27);
                              }
                           } else {
                              return (c >= 0x010D30 && c <= 0x010D39);
                           }
                        }
                     }
                  } else {
                     if(c < 0x010FB0){
                        if(c < 0x010F00){
                           if(c < 0x010EB0){
                              if(c < 0x010EAB){
                                 return (c >= 0x010E80 && c <= 0x010EA9);
                              } else {
                                 return (c >= 0x010EAB && c <= 0x010EAC);
                              }
                           } else {
                              return (c >= 0x010EB0 && c <= 0x010EB1);
                           }
                        } else {
                           if(c < 0x010F30){
                              if(c < 0x010F27){
                                 return (c >= 0x010F00 && c <= 0x010F1C);
                              } else {
                                 return (c >= 0x010F27 && c <= 0x010F27);
                              }
                           } else {
                              return (c >= 0x010F30 && c <= 0x010F50);
                           }
                        }
                     } else {
                        if(c < 0x011066){
                           if(c < 0x011000){
                              if(c < 0x010FE0){
                                 return (c >= 0x010FB0 && c <= 0x010FC4);
                              } else {
                                 return (c >= 0x010FE0 && c <= 0x010FF6);
                              }
                           } else {
                              return (c >= 0x011000 && c <= 0x011046);
                           }
                        } else {
                           if(c < 0x01107F){
                              return (c >= 0x011066 && c <= 0x01106F);
                           } else {
                              return (c >= 0x01107F && c <= 0x0110BA);
                           }
                        }
                     }
                  }
               }
            } else {
               if(c < 0x01130F){
                  if(c < 0x011213){
                     if(c < 0x011176){
                        if(c < 0x011136){
                           if(c < 0x011100){
                              if(c < 0x0110F0){
                                 return (c >= 0x0110D0 && c <= 0x0110E8);
                              } else {
                                 return (c >= 0x0110F0 && c <= 0x0110F9);
                              }
                           } else {
                              return (c >= 0x011100 && c <= 0x011134);
                           }
                        } else {
                           if(c < 0x011150){
                              if(c < 0x011144){
                                 return (c >= 0x011136 && c <= 0x01113F);
                              } else {
                                 return (c >= 0x011144 && c <= 0x011147);
                              }
                           } else {
                              return (c >= 0x011150 && c <= 0x011173);
                           }
                        }
                     } else {
                        if(c < 0x0111CE){
                           if(c < 0x0111C9){
                              if(c < 0x011180){
                                 return (c >= 0x011176 && c <= 0x011176);
                              } else {
                                 return (c >= 0x011180 && c <= 0x0111C4);
                              }
                           } else {
                              return (c >= 0x0111C9 && c <= 0x0111CC);
                           }
                        } else {
                           if(c < 0x011200){
                              if(c < 0x0111DC){
                                 return (c >= 0x0111CE && c <= 0x0111DA);
                              } else {
                                 return (c >= 0x0111DC && c <= 0x0111DC);
                              }
                           } else {
                              return (c >= 0x011200 && c <= 0x011211);
                           }
                        }
                     }
                  } else {
                     if(c < 0x01129F){
                        if(c < 0x011288){
                           if(c < 0x011280){
                              if(c < 0x01123E){
                                 return (c >= 0x011213 && c <= 0x011237);
                              } else {
                                 return (c >= 0x01123E && c <= 0x01123E);
                              }
                           } else {
                              return (c >= 0x011280 && c <= 0x011286);
                           }
                        } else {
                           if(c < 0x01128F){
                              if(c < 0x01128A){
                                 return (c >= 0x011288 && c <= 0x011288);
                              } else {
                                 return (c >= 0x01128A && c <= 0x01128D);
                              }
                           } else {
                              return (c >= 0x01128F && c <= 0x01129D);
                           }
                        }
                     } else {
                        if(c < 0x011300){
                           if(c < 0x0112F0){
                              if(c < 0x0112B0){
                                 return (c >= 0x01129F && c <= 0x0112A8);
                              } else {
                                 return (c >= 0x0112B0 && c <= 0x0112EA);
                              }
                           } else {
                              return (c >= 0x0112F0 && c <= 0x0112F9);
                           }
                        } else {
                           if(c < 0x011305){
                              return (c >= 0x011300 && c <= 0x011303);
                           } else {
                              return (c >= 0x011305 && c <= 0x01130C);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x011366){
                     if(c < 0x011347){
                        if(c < 0x011332){
                           if(c < 0x01132A){
                              if(c < 0x011313){
                                 return (c >= 0x01130F && c <= 0x011310);
                              } else {
                                 return (c >= 0x011313 && c <= 0x011328);
                              }
                           } else {
                              return (c >= 0x01132A && c <= 0x011330);
                           }
                        } else {
                           if(c < 0x01133B){
                              if(c < 0x011335){
                                 return (c >= 0x011332 && c <= 0x011333);
                              } else {
                                 return (c >= 0x011335 && c <= 0x011339);
                              }
                           } else {
                              return (c >= 0x01133B && c <= 0x011344);
                           }
                        }
                     } else {
                        if(c < 0x011357){
                           if(c < 0x011350){
                              if(c < 0x01134B){
                                 return (c >= 0x011347 && c <= 0x011348);
                              } else {
                                 return (c >= 0x01134B && c <= 0x01134D);
                              }
                           } else {
                              return (c >= 0x011350 && c <= 0x011350);
                           }
                        } else {
                           if(c < 0x01135D){
                              return (c >= 0x011357 && c <= 0x011357);
                           } else {
                              return (c >= 0x01135D && c <= 0x011363);
                           }
                        }
                     }
                  } else {
                     if(c < 0x0114C7){
                        if(c < 0x011450){
                           if(c < 0x011400){
                              if(c < 0x011370){
                                 return (c >= 0x011366 && c <= 0x01136C);
                              } else {
                                 return (c >= 0x011370 && c <= 0x011374);
                              }
                           } else {
                              return (c >= 0x011400 && c <= 0x01144A);
                           }
                        } else {
                           if(c < 0x011480){
                              if(c < 0x01145E){
                                 return (c >= 0x011450 && c <= 0x011459);
                              } else {
                                 return (c >= 0x01145E && c <= 0x011461);
                              }
                           } else {
                              return (c >= 0x011480 && c <= 0x0114C5);
                           }
                        }
                     } else {
                        if(c < 0x0115B8){
                           if(c < 0x011580){
                              if(c < 0x0114D0){
                                 return (c >= 0x0114C7 && c <= 0x0114C7);
                              } else {
                                 return (c >= 0x0114D0 && c <= 0x0114D9);
                              }
                           } else {
                              return (c >= 0x011580 && c <= 0x0115B5);
                           }
                        } else {
                           if(c < 0x0115D8){
                              return (c >= 0x0115B8 && c <= 0x0115C0);
                           } else {
                              return (c >= 0x0115D8 && c <= 0x0115DD);
                           }
                        }
                     }
                  }
               }
            }
         }
      } else {
         if(c < 0x01D49E){
            if(c < 0x011DA0){
               if(c < 0x011A47){
                  if(c < 0x01190C){
                     if(c < 0x01171D){
                        if(c < 0x011680){
                           if(c < 0x011650){
                              if(c < 0x011644){
                                 return (c >= 0x011600 && c <= 0x011640);
                              } else {
                                 return (c >= 0x011644 && c <= 0x011644);
                              }
                           } else {
                              return (c >= 0x011650 && c <= 0x011659);
                           }
                        } else {
                           if(c < 0x011700){
                              if(c < 0x0116C0){
                                 return (c >= 0x011680 && c <= 0x0116B8);
                              } else {
                                 return (c >= 0x0116C0 && c <= 0x0116C9);
                              }
                           } else {
                              return (c >= 0x011700 && c <= 0x01171A);
                           }
                        }
                     } else {
                        if(c < 0x0118A0){
                           if(c < 0x011800){
                              if(c < 0x011730){
                                 return (c >= 0x01171D && c <= 0x01172B);
                              } else {
                                 return (c >= 0x011730 && c <= 0x011739);
                              }
                           } else {
                              return (c >= 0x011800 && c <= 0x01183A);
                           }
                        } else {
                           if(c < 0x011909){
                              if(c < 0x0118FF){
                                 return (c >= 0x0118A0 && c <= 0x0118E9);
                              } else {
                                 return (c >= 0x0118FF && c <= 0x011906);
                              }
                           } else {
                              return (c >= 0x011909 && c <= 0x011909);
                           }
                        }
                     }
                  } else {
                     if(c < 0x0119A0){
                        if(c < 0x011937){
                           if(c < 0x011918){
                              if(c < 0x011915){
                                 return (c >= 0x01190C && c <= 0x011913);
                              } else {
                                 return (c >= 0x011915 && c <= 0x011916);
                              }
                           } else {
                              return (c >= 0x011918 && c <= 0x011935);
                           }
                        } else {
                           if(c < 0x011950){
                              if(c < 0x01193B){
                                 return (c >= 0x011937 && c <= 0x011938);
                              } else {
                                 return (c >= 0x01193B && c <= 0x011943);
                              }
                           } else {
                              return (c >= 0x011950 && c <= 0x011959);
                           }
                        }
                     } else {
                        if(c < 0x0119E3){
                           if(c < 0x0119DA){
                              if(c < 0x0119AA){
                                 return (c >= 0x0119A0 && c <= 0x0119A7);
                              } else {
                                 return (c >= 0x0119AA && c <= 0x0119D7);
                              }
                           } else {
                              return (c >= 0x0119DA && c <= 0x0119E1);
                           }
                        } else {
                           if(c < 0x011A00){
                              return (c >= 0x0119E3 && c <= 0x0119E4);
                           } else {
                              return (c >= 0x011A00 && c <= 0x011A3E);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x011D08){
                     if(c < 0x011C38){
                        if(c < 0x011AC0){
                           if(c < 0x011A9D){
                              if(c < 0x011A50){
                                 return (c >= 0x011A47 && c <= 0x011A47);
                              } else {
                                 return (c >= 0x011A50 && c <= 0x011A99);
                              }
                           } else {
                              return (c >= 0x011A9D && c <= 0x011A9D);
                           }
                        } else {
                           if(c < 0x011C0A){
                              if(c < 0x011C00){
                                 return (c >= 0x011AC0 && c <= 0x011AF8);
                              } else {
                                 return (c >= 0x011C00 && c <= 0x011C08);
                              }
                           } else {
                              return (c >= 0x011C0A && c <= 0x011C36);
                           }
                        }
                     } else {
                        if(c < 0x011C92){
                           if(c < 0x011C72){
                              if(c < 0x011C50){
                                 return (c >= 0x011C38 && c <= 0x011C40);
                              } else {
                                 return (c >= 0x011C50 && c <= 0x011C59);
                              }
                           } else {
                              return (c >= 0x011C72 && c <= 0x011C8F);
                           }
                        } else {
                           if(c < 0x011D00){
                              if(c < 0x011CA9){
                                 return (c >= 0x011C92 && c <= 0x011CA7);
                              } else {
                                 return (c >= 0x011CA9 && c <= 0x011CB6);
                              }
                           } else {
                              return (c >= 0x011D00 && c <= 0x011D06);
                           }
                        }
                     }
                  } else {
                     if(c < 0x011D60){
                        if(c < 0x011D3C){
                           if(c < 0x011D3A){
                              if(c < 0x011D0B){
                                 return (c >= 0x011D08 && c <= 0x011D09);
                              } else {
                                 return (c >= 0x011D0B && c <= 0x011D36);
                              }
                           } else {
                              return (c >= 0x011D3A && c <= 0x011D3A);
                           }
                        } else {
                           if(c < 0x011D50){
                              if(c < 0x011D3F){
                                 return (c >= 0x011D3C && c <= 0x011D3D);
                              } else {
                                 return (c >= 0x011D3F && c <= 0x011D47);
                              }
                           } else {
                              return (c >= 0x011D50 && c <= 0x011D59);
                           }
                        }
                     } else {
                        if(c < 0x011D90){
                           if(c < 0x011D6A){
                              if(c < 0x011D67){
                                 return (c >= 0x011D60 && c <= 0x011D65);
                              } else {
                                 return (c >= 0x011D67 && c <= 0x011D68);
                              }
                           } else {
                              return (c >= 0x011D6A && c <= 0x011D8E);
                           }
                        } else {
                           if(c < 0x011D93){
                              return (c >= 0x011D90 && c <= 0x011D91);
                           } else {
                              return (c >= 0x011D93 && c <= 0x011D98);
                           }
                        }
                     }
                  }
               }
            } else {
               if(c < 0x016FE3){
                  if(c < 0x016AF0){
                     if(c < 0x013000){
                        if(c < 0x012000){
                           if(c < 0x011FB0){
                              if(c < 0x011EE0){
                                 return (c >= 0x011DA0 && c <= 0x011DA9);
                              } else {
                                 return (c >= 0x011EE0 && c <= 0x011EF6);
                              }
                           } else {
                              return (c >= 0x011FB0 && c <= 0x011FB0);
                           }
                        } else {
                           if(c < 0x012480){
                              if(c < 0x012400){
                                 return (c >= 0x012000 && c <= 0x012399);
                              } else {
                                 return (c >= 0x012400 && c <= 0x01246E);
                              }
                           } else {
                              return (c >= 0x012480 && c <= 0x012543);
                           }
                        }
                     } else {
                        if(c < 0x016A40){
                           if(c < 0x016800){
                              if(c < 0x014400){
                                 return (c >= 0x013000 && c <= 0x01342E);
                              } else {
                                 return (c >= 0x014400 && c <= 0x014646);
                              }
                           } else {
                              return (c >= 0x016800 && c <= 0x016A38);
                           }
                        } else {
                           if(c < 0x016AD0){
                              if(c < 0x016A60){
                                 return (c >= 0x016A40 && c <= 0x016A5E);
                              } else {
                                 return (c >= 0x016A60 && c <= 0x016A69);
                              }
                           } else {
                              return (c >= 0x016AD0 && c <= 0x016AED);
                           }
                        }
                     }
                  } else {
                     if(c < 0x016E40){
                        if(c < 0x016B50){
                           if(c < 0x016B40){
                              if(c < 0x016B00){
                                 return (c >= 0x016AF0 && c <= 0x016AF4);
                              } else {
                                 return (c >= 0x016B00 && c <= 0x016B36);
                              }
                           } else {
                              return (c >= 0x016B40 && c <= 0x016B43);
                           }
                        } else {
                           if(c < 0x016B7D){
                              if(c < 0x016B63){
                                 return (c >= 0x016B50 && c <= 0x016B59);
                              } else {
                                 return (c >= 0x016B63 && c <= 0x016B77);
                              }
                           } else {
                              return (c >= 0x016B7D && c <= 0x016B8F);
                           }
                        }
                     } else {
                        if(c < 0x016F8F){
                           if(c < 0x016F4F){
                              if(c < 0x016F00){
                                 return (c >= 0x016E40 && c <= 0x016E7F);
                              } else {
                                 return (c >= 0x016F00 && c <= 0x016F4A);
                              }
                           } else {
                              return (c >= 0x016F4F && c <= 0x016F87);
                           }
                        } else {
                           if(c < 0x016FE0){
                              return (c >= 0x016F8F && c <= 0x016F9F);
                           } else {
                              return (c >= 0x016FE0 && c <= 0x016FE1);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x01BC80){
                     if(c < 0x01B150){
                        if(c < 0x018800){
                           if(c < 0x017000){
                              if(c < 0x016FF0){
                                 return (c >= 0x016FE3 && c <= 0x016FE4);
                              } else {
                                 return (c >= 0x016FF0 && c <= 0x016FF1);
                              }
                           } else {
                              return (c >= 0x017000 && c <= 0x0187F7);
                           }
                        } else {
                           if(c < 0x01B000){
                              if(c < 0x018D00){
                                 return (c >= 0x018800 && c <= 0x018CD5);
                              } else {
                                 return (c >= 0x018D00 && c <= 0x018D08);
                              }
                           } else {
                              return (c >= 0x01B000 && c <= 0x01B11E);
                           }
                        }
                     } else {
                        if(c < 0x01BC00){
                           if(c < 0x01B170){
                              if(c < 0x01B164){
                                 return (c >= 0x01B150 && c <= 0x01B152);
                              } else {
                                 return (c >= 0x01B164 && c <= 0x01B167);
                              }
                           } else {
                              return (c >= 0x01B170 && c <= 0x01B2FB);
                           }
                        } else {
                           if(c < 0x01BC70){
                              return (c >= 0x01BC00 && c <= 0x01BC6A);
                           } else {
                              return (c >= 0x01BC70 && c <= 0x01BC7C);
                           }
                        }
                     }
                  } else {
                     if(c < 0x01D185){
                        if(c < 0x01D165){
                           if(c < 0x01BC9D){
                              if(c < 0x01BC90){
                                 return (c >= 0x01BC80 && c <= 0x01BC88);
                              } else {
                                 return (c >= 0x01BC90 && c <= 0x01BC99);
                              }
                           } else {
                              return (c >= 0x01BC9D && c <= 0x01BC9E);
                           }
                        } else {
                           if(c < 0x01D17B){
                              if(c < 0x01D16D){
                                 return (c >= 0x01D165 && c <= 0x01D169);
                              } else {
                                 return (c >= 0x01D16D && c <= 0x01D172);
                              }
                           } else {
                              return (c >= 0x01D17B && c <= 0x01D182);
                           }
                        }
                     } else {
                        if(c < 0x01D400){
                           if(c < 0x01D242){
                              if(c < 0x01D1AA){
                                 return (c >= 0x01D185 && c <= 0x01D18B);
                              } else {
                                 return (c >= 0x01D1AA && c <= 0x01D1AD);
                              }
                           } else {
                              return (c >= 0x01D242 && c <= 0x01D244);
                           }
                        } else {
                           if(c < 0x01D456){
                              return (c >= 0x01D400 && c <= 0x01D454);
                           } else {
                              return (c >= 0x01D456 && c <= 0x01D49C);
                           }
                        }
                     }
                  }
               }
            }
         } else {
            if(c < 0x01E8D0){
               if(c < 0x01D750){
                  if(c < 0x01D53B){
                     if(c < 0x01D4BD){
                        if(c < 0x01D4A9){
                           if(c < 0x01D4A5){
                              if(c < 0x01D4A2){
                                 return (c >= 0x01D49E && c <= 0x01D49F);
                              } else {
                                 return (c >= 0x01D4A2 && c <= 0x01D4A2);
                              }
                           } else {
                              return (c >= 0x01D4A5 && c <= 0x01D4A6);
                           }
                        } else {
                           if(c < 0x01D4BB){
                              if(c < 0x01D4AE){
                                 return (c >= 0x01D4A9 && c <= 0x01D4AC);
                              } else {
                                 return (c >= 0x01D4AE && c <= 0x01D4B9);
                              }
                           } else {
                              return (c >= 0x01D4BB && c <= 0x01D4BB);
                           }
                        }
                     } else {
                        if(c < 0x01D50D){
                           if(c < 0x01D507){
                              if(c < 0x01D4C5){
                                 return (c >= 0x01D4BD && c <= 0x01D4C3);
                              } else {
                                 return (c >= 0x01D4C5 && c <= 0x01D505);
                              }
                           } else {
                              return (c >= 0x01D507 && c <= 0x01D50A);
                           }
                        } else {
                           if(c < 0x01D51E){
                              if(c < 0x01D516){
                                 return (c >= 0x01D50D && c <= 0x01D514);
                              } else {
                                 return (c >= 0x01D516 && c <= 0x01D51C);
                              }
                           } else {
                              return (c >= 0x01D51E && c <= 0x01D539);
                           }
                        }
                     }
                  } else {
                     if(c < 0x01D6C2){
                        if(c < 0x01D54A){
                           if(c < 0x01D546){
                              if(c < 0x01D540){
                                 return (c >= 0x01D53B && c <= 0x01D53E);
                              } else {
                                 return (c >= 0x01D540 && c <= 0x01D544);
                              }
                           } else {
                              return (c >= 0x01D546 && c <= 0x01D546);
                           }
                        } else {
                           if(c < 0x01D6A8){
                              if(c < 0x01D552){
                                 return (c >= 0x01D54A && c <= 0x01D550);
                              } else {
                                 return (c >= 0x01D552 && c <= 0x01D6A5);
                              }
                           } else {
                              return (c >= 0x01D6A8 && c <= 0x01D6C0);
                           }
                        }
                     } else {
                        if(c < 0x01D716){
                           if(c < 0x01D6FC){
                              if(c < 0x01D6DC){
                                 return (c >= 0x01D6C2 && c <= 0x01D6DA);
                              } else {
                                 return (c >= 0x01D6DC && c <= 0x01D6FA);
                              }
                           } else {
                              return (c >= 0x01D6FC && c <= 0x01D714);
                           }
                        } else {
                           if(c < 0x01D736){
                              return (c >= 0x01D716 && c <= 0x01D734);
                           } else {
                              return (c >= 0x01D736 && c <= 0x01D74E);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x01E000){
                     if(c < 0x01DA00){
                        if(c < 0x01D7AA){
                           if(c < 0x01D78A){
                              if(c < 0x01D770){
                                 return (c >= 0x01D750 && c <= 0x01D76E);
                              } else {
                                 return (c >= 0x01D770 && c <= 0x01D788);
                              }
                           } else {
                              return (c >= 0x01D78A && c <= 0x01D7A8);
                           }
                        } else {
                           if(c < 0x01D7CE){
                              if(c < 0x01D7C4){
                                 return (c >= 0x01D7AA && c <= 0x01D7C2);
                              } else {
                                 return (c >= 0x01D7C4 && c <= 0x01D7CB);
                              }
                           } else {
                              return (c >= 0x01D7CE && c <= 0x01D7FF);
                           }
                        }
                     } else {
                        if(c < 0x01DA84){
                           if(c < 0x01DA75){
                              if(c < 0x01DA3B){
                                 return (c >= 0x01DA00 && c <= 0x01DA36);
                              } else {
                                 return (c >= 0x01DA3B && c <= 0x01DA6C);
                              }
                           } else {
                              return (c >= 0x01DA75 && c <= 0x01DA75);
                           }
                        } else {
                           if(c < 0x01DAA1){
                              if(c < 0x01DA9B){
                                 return (c >= 0x01DA84 && c <= 0x01DA84);
                              } else {
                                 return (c >= 0x01DA9B && c <= 0x01DA9F);
                              }
                           } else {
                              return (c >= 0x01DAA1 && c <= 0x01DAAF);
                           }
                        }
                     }
                  } else {
                     if(c < 0x01E130){
                        if(c < 0x01E023){
                           if(c < 0x01E01B){
                              if(c < 0x01E008){
                                 return (c >= 0x01E000 && c <= 0x01E006);
                              } else {
                                 return (c >= 0x01E008 && c <= 0x01E018);
                              }
                           } else {
                              return (c >= 0x01E01B && c <= 0x01E021);
                           }
                        } else {
                           if(c < 0x01E100){
                              if(c < 0x01E026){
                                 return (c >= 0x01E023 && c <= 0x01E024);
                              } else {
                                 return (c >= 0x01E026 && c <= 0x01E02A);
                              }
                           } else {
                              return (c >= 0x01E100 && c <= 0x01E12C);
                           }
                        }
                     } else {
                        if(c < 0x01E2C0){
                           if(c < 0x01E14E){
                              if(c < 0x01E140){
                                 return (c >= 0x01E130 && c <= 0x01E13D);
                              } else {
                                 return (c >= 0x01E140 && c <= 0x01E149);
                              }
                           } else {
                              return (c >= 0x01E14E && c <= 0x01E14E);
                           }
                        } else {
                           if(c < 0x01E800){
                              return (c >= 0x01E2C0 && c <= 0x01E2F9);
                           } else {
                              return (c >= 0x01E800 && c <= 0x01E8C4);
                           }
                        }
                     }
                  }
               }
            } else {
               if(c < 0x01EE5F){
                  if(c < 0x01EE42){
                     if(c < 0x01EE24){
                        if(c < 0x01EE00){
                           if(c < 0x01E950){
                              if(c < 0x01E900){
                                 return (c >= 0x01E8D0 && c <= 0x01E8D6);
                              } else {
                                 return (c >= 0x01E900 && c <= 0x01E94B);
                              }
                           } else {
                              return (c >= 0x01E950 && c <= 0x01E959);
                           }
                        } else {
                           if(c < 0x01EE21){
                              if(c < 0x01EE05){
                                 return (c >= 0x01EE00 && c <= 0x01EE03);
                              } else {
                                 return (c >= 0x01EE05 && c <= 0x01EE1F);
                              }
                           } else {
                              return (c >= 0x01EE21 && c <= 0x01EE22);
                           }
                        }
                     } else {
                        if(c < 0x01EE34){
                           if(c < 0x01EE29){
                              if(c < 0x01EE27){
                                 return (c >= 0x01EE24 && c <= 0x01EE24);
                              } else {
                                 return (c >= 0x01EE27 && c <= 0x01EE27);
                              }
                           } else {
                              return (c >= 0x01EE29 && c <= 0x01EE32);
                           }
                        } else {
                           if(c < 0x01EE3B){
                              if(c < 0x01EE39){
                                 return (c >= 0x01EE34 && c <= 0x01EE37);
                              } else {
                                 return (c >= 0x01EE39 && c <= 0x01EE39);
                              }
                           } else {
                              return (c >= 0x01EE3B && c <= 0x01EE3B);
                           }
                        }
                     }
                  } else {
                     if(c < 0x01EE54){
                        if(c < 0x01EE4B){
                           if(c < 0x01EE49){
                              if(c < 0x01EE47){
                                 return (c >= 0x01EE42 && c <= 0x01EE42);
                              } else {
                                 return (c >= 0x01EE47 && c <= 0x01EE47);
                              }
                           } else {
                              return (c >= 0x01EE49 && c <= 0x01EE49);
                           }
                        } else {
                           if(c < 0x01EE51){
                              if(c < 0x01EE4D){
                                 return (c >= 0x01EE4B && c <= 0x01EE4B);
                              } else {
                                 return (c >= 0x01EE4D && c <= 0x01EE4F);
                              }
                           } else {
                              return (c >= 0x01EE51 && c <= 0x01EE52);
                           }
                        }
                     } else {
                        if(c < 0x01EE5B){
                           if(c < 0x01EE59){
                              if(c < 0x01EE57){
                                 return (c >= 0x01EE54 && c <= 0x01EE54);
                              } else {
                                 return (c >= 0x01EE57 && c <= 0x01EE57);
                              }
                           } else {
                              return (c >= 0x01EE59 && c <= 0x01EE59);
                           }
                        } else {
                           if(c < 0x01EE5D){
                              return (c >= 0x01EE5B && c <= 0x01EE5B);
                           } else {
                              return (c >= 0x01EE5D && c <= 0x01EE5D);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x01EEA5){
                     if(c < 0x01EE79){
                        if(c < 0x01EE67){
                           if(c < 0x01EE64){
                              if(c < 0x01EE61){
                                 return (c >= 0x01EE5F && c <= 0x01EE5F);
                              } else {
                                 return (c >= 0x01EE61 && c <= 0x01EE62);
                              }
                           } else {
                              return (c >= 0x01EE64 && c <= 0x01EE64);
                           }
                        } else {
                           if(c < 0x01EE74){
                              if(c < 0x01EE6C){
                                 return (c >= 0x01EE67 && c <= 0x01EE6A);
                              } else {
                                 return (c >= 0x01EE6C && c <= 0x01EE72);
                              }
                           } else {
                              return (c >= 0x01EE74 && c <= 0x01EE77);
                           }
                        }
                     } else {
                        if(c < 0x01EE8B){
                           if(c < 0x01EE80){
                              if(c < 0x01EE7E){
                                 return (c >= 0x01EE79 && c <= 0x01EE7C);
                              } else {
                                 return (c >= 0x01EE7E && c <= 0x01EE7E);
                              }
                           } else {
                              return (c >= 0x01EE80 && c <= 0x01EE89);
                           }
                        } else {
                           if(c < 0x01EEA1){
                              return (c >= 0x01EE8B && c <= 0x01EE9B);
                           } else {
                              return (c >= 0x01EEA1 && c <= 0x01EEA3);
                           }
                        }
                     }
                  } else {
                     if(c < 0x02B820){
                        if(c < 0x020000){
                           if(c < 0x01FBF0){
                              if(c < 0x01EEAB){
                                 return (c >= 0x01EEA5 && c <= 0x01EEA9);
                              } else {
                                 return (c >= 0x01EEAB && c <= 0x01EEBB);
                              }
                           } else {
                              return (c >= 0x01FBF0 && c <= 0x01FBF9);
                           }
                        } else {
                           if(c < 0x02B740){
                              if(c < 0x02A700){
                                 return (c >= 0x020000 && c <= 0x02A6DD);
                              } else {
                                 return (c >= 0x02A700 && c <= 0x02B734);
                              }
                           } else {
                              return (c >= 0x02B740 && c <= 0x02B81D);
                           }
                        }
                     } else {
                        if(c < 0x030000){
                           if(c < 0x02F800){
                              if(c < 0x02CEB0){
                                 return (c >= 0x02B820 && c <= 0x02CEA1);
                              } else {
                                 return (c >= 0x02CEB0 && c <= 0x02EBE0);
                              }
                           } else {
                              return (c >= 0x02F800 && c <= 0x02FA1D);
                           }
                        } else {
                           if(c < 0x0E0100){
                              return (c >= 0x030000 && c <= 0x03134A);
                           } else {
                              return (c >= 0x0E0100 && c <= 0x0E01EF);
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }
}
